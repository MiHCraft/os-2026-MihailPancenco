# Lab 09 — Watching System Calls with strace

The runs used Ubuntu 26.04.1 LTS (AArch64) in VirtualBox, strace 6.19 and GCC 15.2.0.

## 1. Trace `ls`

In a directory containing two small files, `alpha.txt` and `beta.txt`, the filtered command was:

```sh
strace -f -e trace=openat,read,write,close -o ../ls-filtered.strace ls -l
```

The listing reached the terminal via `write(1, ..., 103) = 103`. File descriptor 1 is standard output. The return value confirms that the call wrote all 103 bytes. The filter recorded 85 calls across the four named syscall types.

## 2. Write and read a file

`syscalls.c` opens `note.txt` for writing, writes the 14 bytes of `hello, kernel\n`, closes the file, opens it for reading, and verifies the bytes it reads. To reproduce the run from the submission directory:

```sh
gcc -Wall -Wextra -Werror -o /tmp/lab09-syscalls syscalls.c
strace -e trace=openat,read,write,close -o /tmp/lab09-syscalls.strace /tmp/lab09-syscalls
wc -c note.txt
```

The two calls to C's `open` appear as `openat` in the trace. The write-only open returned 3, `write(3, ..., 14)` returned 14, and `close(3)` returned 0. The read-only open reused descriptor 3, and `read(3, ..., 14)` returned 14. The file was 14 bytes long. The C string terminator was excluded from the write.

Descriptors 0, 1 and 2 were already inherited as standard input, standard output and standard error. The first file open therefore returned 3, the lowest free descriptor. After the close it was available again.

## 3. Count calls

From the two-file sample directory:

```sh
strace -f -o ../ls-full.strace ls -l
grep -Ec '^[0-9]+ +[[:alnum:]_]+\(' ../ls-full.strace
strace -f -c -e trace=openat ls -l >/dev/null
```

The unfiltered trace contains **264 syscall entries**, excluding the process-exit status marker. The separate summary contains **31 `openat` calls**, including **one failed call**. These are counts for the observed runs. The raw traces and the `openat` summary accompany the source.
