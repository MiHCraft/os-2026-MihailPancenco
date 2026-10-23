# Lab 06 - Inside the xv6 File System

## Environment and evidence

Tested on 23 October 2026 with MIT xv6-riscv commit `f780d7850765d74cbdcd1fff4b822d8829f7c9bd`, RISC-V GNU tools and QEMU. The recorded session used a combined image containing labs 04, 06 and 08, so executable sizes and assigned inode numbers can differ from the teacher's example or a minimal image. Each lab Makefile also built independently. `terminal-output.txt` contains the full shared test session. The source constants and line numbers below were read from the pinned checkout.

## Part 1 - What ls shows

The four columns in xv6 `ls` are name, numeric type, inode number and logical size in bytes. They are different from Linux `ls -l` permissions/ownership columns.

### 1. Types 1, 2 and 3

`kernel/stat.h` defines `T_DIR = 1` (directory), `T_FILE = 2` (regular file), and `T_DEVICE = 3` (device). `console` has type 3; it accesses a device driver instead of ordinary file data blocks.

### 2. Root inode

The root inode is 1, set by `ROOTINO` in `kernel/fs.h`. Its `.` and `..` entries both name inode 1 because the root is its own parent. Representative recorded rows were:

```text
.              1 1 1024
..             1 1 1024
README         2 2 2441
console        3 32 0
```

### 3. Empty directory size

```text
$ mkdir a
$ ls a
.              1 35 32
..             1 1 1024
```

An entry is `sizeof(struct dirent) = 16` bytes: a two-byte inode number and a 14-byte name. A new empty directory contains `.` and `..`, so its logical size is `2 * 16 = 32` bytes. It can still occupy a whole allocated filesystem block. An entry whose name uses all 14 bytes has no terminating NUL in the disk record.

## Part 2 - mystat and hard links

`user/mystat.c` accepts one or more paths, calls `stat`, maps numeric types to readable names and prints inode, link count and byte size. A failed path reports to descriptor 2 and does not prevent later paths from being processed. A usage or stat error results in a nonzero exit status.

```text
$ mystat README . console
README: file, inode 2, links 1, size 2441 bytes
.: directory, inode 1, links 2, size 1024 bytes
console: device, inode 32, links 1, size 0 bytes
$ ln README r2
$ mystat README r2
README: file, inode 2, links 2, size 2441 bytes
r2: file, inode 2, links 2, size 2441 bytes
$ rm README
$ mystat r2
r2: file, inode 2, links 1, size 2441 bytes
$ cat r2 | wc
48 336 2441
```

### 1. What changed after ln and rm

Before linking, README had inode 2, size 2441 and one link. `ln README r2` makes both names resolve to inode 2, raises the shared link count to 2 and does not copy the data. Unlinking README removes that name and reduces the count to 1; r2's inode, type, size and contents remain unchanged. `cat r2 | wc` confirms that its 2441 bytes are still readable.

The root directory in this session already had a subdirectory from lab 04, so its link count was 2 rather than the initial image's 1. xv6 does not count `.` the same way as the Linux directory convention from lab 05; do not apply Linux's new-directory link count mechanically to xv6.

### 2. Where unlink decreases nlink and when storage is freed

At the pinned revision, `kernel/sysfile.c:244`, within `sys_unlink`, contains `ip->nlink--;`, followed by `iupdate(ip)` and `iunlockput(ip)`. The similarly spelled decrement in `sys_link` is error rollback, not the successful unlink path.

```sh
grep -n 'ip->nlink--' kernel/sysfile.c
sed -n '235,250p' kernel/sysfile.c
sed -n '345,380p' kernel/fs.c
```

The directory slot is cleared before that decrement. In `kernel/fs.c`, `iput` reclaims the inode when its link count is zero and the last in-memory reference is being released (`ref == 1` at entry). It calls `itrunc` to free direct and indirect data blocks and later makes the inode reusable. If a process still has the file open, its reference delays reclamation until close/exit releases it. These operations occur within filesystem transactions.

### 3. Fields of the on-disk inode

`struct dinode` contains `short type`, `short major`, `short minor`, `short nlink`, `uint size`, and `uint addrs[NDIRECT + 1]`. With this layout it occupies 64 bytes. `major` and `minor` identify a device driver/device number for device inodes; `addrs` stores 12 direct block addresses and one indirect address. The inode has no filename, owner UID, owner GID, access-mode bits or timestamps. This baseline has no symbolic-link type and no Unix permission checking. The separate in-memory inode adds bookkeeping such as reference counts and locking.

## Part 3 - Filesystem limits

### 1. Long names and DIRSIZ

```text
$ mkdir averyveryverylongname
$ ls
[excerpt]
averyveryveryl 1 36 32
```

`DIRSIZ = 14`, so the stored component is the first 14 characters, `averyveryveryl`. Two longer names with the same first 14 bytes can resolve to the same component. This is a fixed-size name limitation, not terminal clipping.

### 2. Largest file calculation

```text
BSIZE = 1024 bytes
NDIRECT = 12 blocks
NINDIRECT = BSIZE / sizeof(uint) = 1024 / 4 = 256 blocks
MAXFILE = NDIRECT + NINDIRECT = 268 data blocks
Maximum content = (12 + 256) * 1024 = 274432 bytes = 268 KiB
```

The indirect block stores 256 block numbers, not file content, so it contributes addressing capacity but is not an extra data block in this sum. A maximum-size file also consumes an indirect metadata block, its inode and other filesystem metadata. The result is the per-file addressing limit; free space can impose a lower practical limit.

### 3. Disk layout from mkfs

Recorded during the actual build:

```text
nmeta 47 (boot, super, log blocks 31, inode blocks 13, bitmap blocks 1) blocks 1953 total 2000
```

| Region | Blocks | Block indices |
| --- | --- | --- |
| Boot and superblock | 2 | 0 and 1 |
| Log (header plus 30 payload blocks) | 31 | 2 through 32 |
| Inodes | 13 | 33 through 45 |
| Free-block bitmap | 1 | 46 |
| Data region | 1953 | 47 through 1999 |

The total is `2 + 31 + 13 + 1 + 1953 = 2000` blocks, or 2,048,000 bytes. The data-region size includes blocks already occupied by the initial directories and user programs; it is not a free-block count. Older xv6 revisions can print a 30-block log and 1954 data blocks; the recorded checkout reserves a separate log header and prints 31.

## Part 4 - Recursive find

`user/find.c` walks from the supplied path and compares each last component using `strcmp`. It handles regular files and directories, skips free entries (`inum == 0`) and explicitly skips `.` and `..`. A 14-byte on-disk name is copied into a 15-byte buffer and NUL-terminated before comparison. Constructed paths are checked against `MAXPATH` and trailing slashes on the starting path are normalized.

To avoid consuming the 16-descriptor per-process limit with recursive depth, each directory entry read opens the directory, skips to that entry, reads it, and closes the descriptor before recursion. A shared path buffer also reduces stack use. This trades O(n squared) reads per directory for bounded descriptor use; it is adequate for the small xv6 tree. As with the basic exercise, the walk assumes directories are not concurrently modified. Paths and the one-page user stack still bound the maximum supported depth.

### Nested-directory test

For an independent run, use a fresh image, as the handout requests. The combined recorded session already contained `a` and a hard link named `r2` from earlier experiments; it reused `a` and removed the old `r2` before linking `cat`.

```text
$ mkdir a/b
$ echo x > a/b/r2
$ echo y > a/r2
$ rm r2
$ ln cat r2
```

```text
$ find . r2
./a/b/r2
./a/r2
./r2
$ find a b
a/b
```

The three matches have the same last component but different paths. The directory `a/b` is also a match when searching for `b`; the program is not restricted to regular files.

### Error handling and trailing slash

```text
$ mystat missing cat
mystat: cannot stat missing
cat: file, inode 3, links 2, size 36280 bytes
$ find no-such r2
find: cannot stat no-such
$ find a/ b
a/b
$ find a r2 -x
usage: find <dir> <name> [-n]
$ find
usage: find <dir> <name> [-n]
```

The stat error did not suppress the valid `cat` result. A nonexistent starting path gives an error rather than silence; a bad optional argument or missing arguments gives usage. `find a/ b` produces the same normalized result as `find a b`.

## Stretch - Show inode numbers

```text
$ find . r2 -n
./a/b/r2 inode 38
./a/r2 inode 39
./r2 inode 3
$ mystat cat r2
cat: file, inode 3, links 2, size 36280 bytes
r2: file, inode 3, links 2, size 36280 bytes
```

Only `./r2` has inode 3, the same as `cat`. The files `./a/b/r2` and `./a/r2` are independent files, inodes 38 and 39. Matching filenames do not imply shared content or inode identity; matching inode numbers on the same filesystem do.

## Submission checklist

Required: `user/mystat.c`, `user/find.c`, the complete xv6 `Makefile`, and `notes.md`. `find` includes the optional `-n` mode. `README.md` explains copying the overlay into xv6. The separate report directory contains the LaTeX report and compiled PDF.
