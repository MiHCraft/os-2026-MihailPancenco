misa@UbuntuVM:~$ mkdir -p ~/os-lab1 && cd ~/os-lab1
# I've created a folder and entered it. -p flag means that it will create necessary folders if the path has them but they do not exist.

misa@UbuntuVM:~/os-lab1$ whoami
misa 
# it is my username in that OS

misa@UbuntuVM:~/os-lab1$ uname -a
Linux UbuntuVM 7.0.0-34-generic #34-Ubuntu SMP PREEMPT_DYNAMIC Wed Sep  2 14:34:54 UTC 2026 aarch64 GNU/Linux
# Here I see the kernel that managing this machine. It is Ubuntu, working on an Arm architecture, because the processor is ARM, because Ubuntu is in Virtual Machine and that Virtual Machine is in the mac OS in the macbook.

misa@UbuntuVM:~/os-lab1$ uptime
 19:49:16 up 11:06,  1 user,  load average: 0.14, 0.14, 0.06
# Here we see how much time spended scince first launch of OC. Probably 20 Hours. 
 
misa@UbuntuVM:~/os-lab1$ 



misa@UbuntuVM:~/os-lab1$ 
misa@UbuntuVM:~/os-lab1$ pwd
/home/misa/os-lab1
# pring working directory
misa@UbuntuVM:~/os-lab1$ ls -la /
total 80
drwxr-xr-x  20 root root  4096 Sep 28 15:07 .
drwxr-xr-x  20 root root  4096 Sep 28 15:07 ..
lrwxrwxrwx   1 root root     7 Apr 20 08:46 bin -> usr/bin
drwxr-xr-x   4 root root  4096 Sep 29 08:51 boot
dr-xr-xr-x   2 root root  4096 Sep 28 15:05 cdrom
drwxr-xr-x  18 root root  4080 Sep 29 19:40 dev
drwxr-xr-x 142 root root 12288 Sep 28 15:28 etc
drwxr-xr-x   3 root root  4096 Sep 28 15:27 home
lrwxrwxrwx   1 root root     7 Apr 20 08:46 lib -> usr/lib
drwx------   2 root root 16384 Sep 28 15:08 lost+found
drwxr-xr-x   2 root root  4096 Aug 26 09:14 media
drwxr-xr-x   2 root root  4096 Aug 26 09:14 mnt
drwxr-xr-x   2 root root  4096 Aug 26 09:14 opt
dr-xr-xr-x 288 root root     0 Sep 29 08:42 proc
drwx------   5 root root  4096 Sep 28 15:27 root
drwxr-xr-x  45 root root  1060 Sep 29 18:31 run
lrwxrwxrwx   1 root root     8 Apr 20 08:46 sbin -> usr/sbin
drwxr-xr-x  14 root root  4096 Aug 26 09:41 snap
drwxr-xr-x   2 root root  4096 Aug 26 09:14 srv
dr-xr-xr-x  13 root root     0 Sep 29 08:42 sys
drwxrwxrwt  16 root root   360 Sep 29 20:14 tmp
drwxr-xr-x  11 root root  4096 Aug 26 09:14 usr
drwxr-xr-x  14 root root  4096 Sep 28 15:27 var

# list of the core directory
misa@UbuntuVM:~/os-lab1$ ls -la ~
total 84
drwxr-x--- 17 misa misa 4096 Sep 28 16:05 .
drwxr-xr-x  3 root root 4096 Sep 28 15:27 ..
-rw-------  1 misa misa  341 Sep 29 19:51 .bash_history
-rw-r--r--  1 misa misa  220 Feb 13  2026 .bash_logout
-rw-r--r--  1 misa misa 3771 Feb 13  2026 .bashrc
drwx------ 13 misa misa 4096 Sep 29 19:50 .cache
drwx------ 15 misa misa 4096 Sep 29 08:54 .config
drwx------  2 misa misa 4096 Sep 29 19:52 .gnupg
drwx------  4 misa misa 4096 Sep 28 15:28 .local
-rw-r--r--  1 misa misa  807 Feb 13  2026 .profile
drwx------  2 misa misa 4096 Sep 28 15:27 .ssh
drwxr-xr-x  2 misa misa 4096 Sep 29 19:58 Desktop
drwxr-xr-x  2 misa misa 4096 Sep 28 15:28 Documents
drwxr-xr-x  2 misa misa 4096 Sep 28 15:28 Downloads
drwxr-xr-x  2 misa misa 4096 Sep 28 15:28 Music
drwxr-xr-x  2 misa misa 4096 Sep 28 15:28 Pictures
drwxr-xr-x  2 misa misa 4096 Sep 28 15:28 Public
drwxr-xr-x  2 misa misa 4096 Sep 28 15:28 Templates
drwxr-xr-x  2 misa misa 4096 Sep 28 15:28 Videos
drwxrwxr-x  2 misa misa 4096 Sep 28 15:52 os-lab1
drwx------  5 misa misa 4096 Sep 29 19:50 snap

# list of the home directory
misa@UbuntuVM:~/os-lab1$ cd /etc && ls | head
ModemManager
NetworkManager
PackageKit
UPower
X11
adduser.conf
alsa
alternatives
anacrontab
apm
misa@UbuntuVM:/etc$ 

#top 10 results of /etc directory



misa@UbuntuVM:/etc$ cd ~os-lab1
bash: cd: ~os-lab1: No such file or directory
# mistype

misa@UbuntuVM:/etc$ cd ~/os-lab1

# changed directory to /os-lab1
misa@UbuntuVM:~/os-lab1$ mkdir demo && cd demo

# create new folder, enter that folder
misa@UbuntuVM:~/os-lab1/demo$ echo "hello operating systems" > note.txt

# Create new file with that text
misa@UbuntuVM:~/os-lab1/demo$ cp note.txt copy.txt

# Make a copy of a file named copy.txt
misa@UbuntuVM:~/os-lab1/demo$ mv copy.txt renamed.txt

# 'Move' the file to another place, in that case, just rename
misa@UbuntuVM:~/os-lab1/demo$ ls -l
total 8
-rw-rw-r-- 1 misa misa 24 Sep 29 20:44 note.txt
-rw-rw-r-- 1 misa misa 24 Sep 29 20:44 renamed.txt

# we see both files
misa@UbuntuVM:~/os-lab1/demo$ rm renamed.txt

#remove copied renamed file
misa@UbuntuVM:~/os-lab1/demo$ 









misa@UbuntuVM:~/os-lab1/demo$ ls -l note.txt
-rw-rw-r-- 1 misa misa 24 Sep 29 20:44 note.txt

#see the permisions. Me and my group can read and write that file, others can just read.

misa@UbuntuVM:~/os-lab1/demo$ chmod 600 note.txt

#change permissions
misa@UbuntuVM:~/os-lab1/demo$ ls -l note.txt
-rw------- 1 misa misa 24 Sep 29 20:44 note.txt

#took away permissions from others
misa@UbuntuVM:~/os-lab1/demo$ chmod 644 note.txt

#give them the permission only to read
misa@UbuntuVM:~/os-lab1/demo$ ls -l note.txt
-rw-r--r-- 1 misa misa 24 Sep 29 20:44 note.txt

#make sure that it is done what we want
misa@UbuntuVM:~/os-lab1/demo$ 

# (1) Who owns the files you just created, and which group?
# (2) What do the ten characters at the start of `ls -l` mean for note.txt after chmod 600?
# (3) Name two directories directly under / and say, in one line each, what they hold.

# (1)The files I've just created I own. (2)First characters show the permissions of
# who can do what with that file. First - me, second - my group, third - others. r - read. w - write. x - execute. (1)misa - is the owner of file, and misa - is the group to which file belongs. Yes, both named misa.

# chmod numbers 1 to 7 represented in binary as 000 to 111, each bit for separate permission: one for read, another for write, third for execution.


# (3)
# drwxr-xr-x   3 root root  4096 Sep 28 15:27 home    : inside is the 'home', i.e. user folder, which has folders for him: Desktop, Documents, Music, etc. 
# drwxr-xr-x 142 root root 12288 Sep 28 15:28 etc     : inside is the folder with system-wide configuration files.




misa@UbuntuVM:~/Desktop$ ps aux | head
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.1  0.3  27416 18204 ?        Ss   12:19   0:01 /usr/lib/systemd/systemd --switched-root --system --deserialize=52 splash noprompt noshell automatic-ubiquity crashkernel=2G-4G:320M,4G-32G:512M,32G-64G:1024M,64G-128G:2048M,128G-:4096M
root           2  0.0  0.0      0     0 ?        S    12:19   0:00 [kthreadd]
root           3  0.0  0.0      0     0 ?        S    12:19   0:00 [pool_workqueue_release]
root           4  0.0  0.0      0     0 ?        I<   12:19   0:00 [kworker/R-rcu_gp]
root           5  0.0  0.0      0     0 ?        I<   12:19   0:00 [kworker/R-sync_wq]
root           6  0.0  0.0      0     0 ?        I<   12:19   0:00 [kworker/R-kvfree_rcu_reclaim]
root           7  0.0  0.0      0     0 ?        I<   12:19   0:00 [kworker/R-slub_flushwq]
root           8  0.0  0.0      0     0 ?        I<   12:19   0:00 [kworker/R-netns]
root          10  0.0  0.0      0     0 ?        I<   12:19   0:00 [kworker/0:0H-kblockd]
misa@UbuntuVM:~/Desktop$ ps aux | wc -l
227
misa@UbuntuVM:~/Desktop$ 


Tasks: 223 total,   1 running, 222 sleeping,   0 stopped,   0 zombie
%Cpu(s):  4.2 us,  1.2 sy,  0.0 ni, 94.0 id,  0.0 wa,  0.0 hi,  0.5 si,  0.0 st 
MiB Mem :   5235.4 total,    585.4 free,   2719.1 used,   2143.5 buff/cache     
MiB Swap:      0.0 total,      0.0 free,      0.0 used.   2516.3 avail Mem 

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                     
   3840 misa      20   0 6221956 525068 173672 S  17.6   9.8   1:23.04 gnome-shell                 
   5619 misa      20   0 3587768 522544 135348 S  17.3   9.7   0:15.33 ptyxis                      
    101 root      20   0       0      0      0 I   1.0   0.0   0:01.89 kworker/u24:5-events_power+ 
     15 root      20   0       0      0      0 I   0.3   0.0   0:00.43 rcu_preempt                 
    897 root      20   0       0      0      0 I   0.3   0.0   0:01.27 kworker/u24:7-events_unbou+ 
      1 root      20   0   27416  18204  10924 S   0.0   0.3   0:01.89 systemd                     
      2 root      20   0       0      0      0 S   0.0   0.0   0:00.00 kthreadd                    
      3 root      20   0       0      0      0 S   0.0   0.0   0:00.00 pool_workqueue_release      
      4 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/R-rcu_gp            
      5 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/R-sync_wq           
      6 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/R-kvfree_rcu_recla+ 
      7 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/R-slub_flushwq      
      8 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/R-netns             
     10 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/0:0H-kblockd        
     11 root      20   0       0      0      0 I   0.0   0.0   0:00.46 kworker/0:1-events          
     13 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/R-mm_percpu_wq      
     14 root      20   0       0      0      0 S   0.0   0.0   0:00.09 ksoftirqd/0                 
     16 root      20   0       0      0      0 S   0.0   0.0   0:00.00 rcu_exp_par_gp_kthread_wor+ 
     17 root      20   0       0      0      0 S   0.0   0.0   0:00.05 rcu_exp_gp_kthread_worker   
     18 root      rt   0       0      0      0 S   0.0   0.0   0:00.00 migration/0                 
     19 root     -51   0       0      0      0 S   0.0   0.0   0:00.00 idle_inject/0               
     20 root      20   0       0      0      0 S   0.0   0.0   0:00.00 cpuhp/0    



isa@UbuntuVM:~/Desktop$ sleep 300 &
[1] 7609

# start waiting 300 seconds, or 5 minutes and do it in background(&)
# 7609 is a PID of a process

misa@UbuntuVM:~/Desktop$ jobs
[1]+  Running                    sleep 300 &
# all background processes
misa@UbuntuVM:~/Desktop$ ps -ef | grep sleep
misa        7609    5692  0 12:53 pts/0    00:00:00 sleep 300
misa        7620    5692  0 12:53 pts/0    00:00:00 grep --color=auto sleep
# show processes that contains the 'sleep' word. Program finds my process and finds itself as a process that contains that word.
misa@UbuntuVM:~/Desktop$ kill 7609
[1]+  Terminated                 sleep 300

# ask os to terminate the process by PID
misa@UbuntuVM:~/Desktop$ 



misa@UbuntuVM:~/Desktop$ sleep 500 &
[1] 7723
# start background process
misa@UbuntuVM:~/Desktop$ PID=$!
#  save in the PID variable the PID of the last background process. 

misa@UbuntuVM:~/Desktop$ ls /proc/$PID/
attr             environ            limits      ns             root          statm
autogroup        exe                loginuid    numa_maps      sched         status
auxv             fd                 map_files   oom_adj        schedstat     syscall
cgroup           fdinfo             maps        oom_score      sessionid     task
clear_refs       gid_map            mem         oom_score_adj  setgroups     timens_offsets
cmdline          io                 mountinfo   pagemap        smaps         timers
comm             ksm_merging_pages  mounts      patch_state    smaps_rollup  timerslack_ns
coredump_filter  ksm_stat           mountstats  personality    stack         uid_map
cwd              latency            net         projid_map     stat          wchan

# see that is inside the pseudo-file system
misa@UbuntuVM:~/Desktop$ cat /proc/$PID/status | head -20
Name:	sleep
Umask:	0002
State:	S (sleeping)
Tgid:	7723
Ngid:	0
Pid:	7723
PPid:	5692
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	27 1000 
NStgid:	7723
NSpid:	7723
NSpgid:	7723
NSsid:	5692
Kthread:	0
VmPeak:	   16424 kB
VmSize:	   16424 kB
VmLck:	       0 kB

# top 20 lines of status file. 
misa@UbuntuVM:~/Desktop$ kill $PID
[1]+  Terminated                 sleep 500

#finally kill it
misa@UbuntuVM:~/Desktop$ 







(1) What is the PID of process number 1, and what is it (look it up)?
PID is 1. 
root           1  0.1  0.3  27416 18204 ?        Ss   12:19   0:01 /usr/lib/systemd/systemd --switched-root -
It is systemd, the first userspace process started by the Linux kernel, responsible for starting and managing other system services.

(2) Roughly how many processes were running on your idle VM?
Tasks: 223 total,   1 running, 222 sleeping,   0 stopped,   0 zombie

So, on idle vm machine roughly around 2020 tasks. 

(3) From /proc/<pid>/status, what does the "State:" line say for your sleeping process?
The State: line says S (sleeping), meaning that the sleep process was waiting and not actively using the CPU.









isa@UbuntuVM:~/Desktop$ free -h
               total        used        free      shared  buff/cache   available
Mem:           5.1Gi       2.9Gi       316Mi        59Mi       2.1Gi       2.2Gi
Swap:             0B          0B          0B

# We have so few free memory because much of it used for cache, but still available.
# We don't have swap file.
misa@UbuntuVM:~/Desktop$ cat /proc/meminfo | head -6
MemTotal:        5361020 kB
MemFree:          313804 kB
MemAvailable:    2321144 kB
Buffers:           62916 kB
Cached:          2100192 kB
SwapCached:            0 kB

# Same info using pseudo tree
misa@UbuntuVM:~/Desktop$ sleep 300 & PID=$!
[1] 8201

# start process and save in variable it's PID
misa@UbuntuVM:~/Desktop$ grep VmRSS /proc/$PID/status
VmRSS:	    6356 kB

# using grep (global regular expression print) find VmRSS in the status folder and show this. 
# VmRSS shows how many RAM that process uses. VmRSS = Virtual Memory Resident Set Size. That is real in the memory. 
misa@UbuntuVM:~/Desktop$ kill $PID
[1]+  Terminated                 sleep 300

# kill unnecessary process
misa@UbuntuVM:~/Desktop$ 


(1) How much total RAM does the VM have, and how much is free?
The VM has 5.1 GiB of total RAM, with about 316 MiB free. However, about 2.2 GiB is available, because some RAM used for cache can be reclaimed.

(2) What is swap, and how much is configured?
Swap is disk space that can be used as an extension of RAM when physical memory is insufficient. This VM has no swap configured (0 B).

(3) How much resident memory (VmRSS) does a bare `sleep` process use, and does that surprise you?
A bare sleep process uses about 6356 kB (6.2 MiB) of resident memory (VmRSS). Yes, this surprised me, because sleep does almost nothing, but it still requires several megabytes of RAM.





misa@UbuntuVM:~/Desktop$ df -h 
Filesystem      Size  Used Avail Use% Mounted on
tmpfs           1.1G  1.8M  1.1G   1% /run
/dev/sda2        48G  6.9G   39G  16% /
tmpfs           2.6G     0  2.6G   0% /dev/shm
efivarfs        256K  9.1K  247K   4% /sys/firmware/efi/efivars
none            1.0M     0  1.0M   0% /run/credentials/systemd-journald.service
tmpfs           2.6G  8.0K  2.6G   1% /tmp
none            1.0M     0  1.0M   0% /run/credentials/systemd-resolved.service
/dev/sda1       1.1G  6.6M  1.1G   1% /boot/efi
tmpfs           524M   96K  524M   1% /run/user/1000
/dev/sr0         51M   51M     0 100% /run/media/misa/VBox_GAs_7.2.2

# df -h => disk free, human readable
# shows usage of disk with file systems

misa@UbuntuVM:~/Desktop$ lsblk
NAME   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
loop0    7:0    0     4K  1 loop /snap/bare/5
loop1    7:1    0  61.9M  1 loop /snap/core24/1644
loop2    7:2    0  90.7M  1 loop /snap/desktop-security-center/190
loop4    7:4    0 251.4M  1 loop /snap/firefox/8994
loop5    7:5    0 247.5M  1 loop /snap/firefox/8762
loop6    7:6    0 552.9M  1 loop /snap/gnome-46-2404/154
loop7    7:7    0 188.2M  1 loop /snap/mesa-2404/1836
loop8    7:8    0  91.7M  1 loop /snap/gtk-common-themes/1535
loop9    7:9    0  79.9M  1 loop /snap/prompting-client/229
loop10   7:10   0  17.5M  1 loop /snap/prompting-client/221
loop11   7:11   0  10.9M  1 loop /snap/snap-store/1391
loop12   7:12   0  43.4M  1 loop /snap/snapd/27709
loop13   7:13   0   804K  1 loop /snap/snapd-desktop-integration/396
loop14   7:14   0  38.6M  1 loop /snap/snapd/28255
loop15   7:15   0  90.7M  1 loop /snap/desktop-security-center/207
sda      8:0    0    50G  0 disk 
├─sda1   8:1    0     1G  0 part /boot/efi
└─sda2   8:2    0  48.9G  0 part /
sr0     11:0    1  50.7M  1 rom  /run/media/misa/VBox_GAs_7.2.2


# lsblk = list block devices. sda, for example, is a disk, and sda1 and sda2 are the partisions.
misa@UbuntuVM:~/Desktop$ du -sh ~/os-lab1
12K	/home/misa/os-lab1

# du = disk usage. -s = summary. -h = human readable. 
# shows the amount of memory used for this folder. 
misa@UbuntuVM:~/Desktop$ ls -l /dev | head
total 0
crw-r--r--  1 root    root     10, 235 Oct  5 12:25 autofs
drwxr-xr-x  2 root    root        440 Oct  5 13:07 block
drwxr-xr-x  2 root    root         80 Oct  5 12:19 bsg
crw-------  1 root    root     10, 234 Oct  5 12:19 btrfs-control
drwxr-xr-x  3 root    root         60 Jan  1  1970 bus
lrwxrwxrwx+ 1 root    root          3 Oct  5 12:19 cdrom -> sr0
drwxr-xr-x  2 root    root       3820 Oct  5 14:04 char
crw-------  1 root    tty       5,   1 Oct  5 12:25 console
lrwxrwxrwx  1 root    root         11 Oct  5 12:19 core -> /proc/kcore

# devices. The file interface to them
misa@UbuntuVM:~/Desktop$ mount | head
tmpfs on /run type tmpfs (rw,nosuid,nodev,size=1072204k,nr_inodes=819200,mode=755,inode64)
/dev/sda2 on / type ext4 (rw,relatime)
devtmpfs on /dev type devtmpfs (rw,nosuid,size=1772372k,nr_inodes=443093,mode=755,inode64)
tmpfs on /dev/shm type tmpfs (rw,nosuid,nodev,inode64,usrquota)
devpts on /dev/pts type devpts (rw,nosuid,noexec,relatime,gid=5,mode=600,ptmxmode=000)
sysfs on /sys type sysfs (rw,nosuid,nodev,noexec,relatime)
securityfs on /sys/kernel/security type securityfs (rw,nosuid,nodev,noexec,relatime)
cgroup2 on /sys/fs/cgroup type cgroup2 (rw,nosuid,nodev,noexec,relatime,nsdelegate,memory_recursiveprot,memory_hugetlb_accounting)
none on /sys/fs/pstore type pstore (rw,nosuid,nodev,noexec,relatime)
efivarfs on /sys/firmware/efi/efivars type efivarfs (rw,nosuid,nodev,noexec,relatime)

#show mounted file systems. top 10 lines.
misa@UbuntuVM:~/Desktop$ 

(1) Which device is your root filesystem "/" mounted on?
The root filesystem / is mounted on /dev/sda2.

(2) Give one entry from /dev and say what real thing it stands for.
One example is /dev/cdrom, which represents the virtual CD/DVD drive (sr0) in the VM.
Another example is **`/dev/console`**, which represents the system console and provides a file interface for input and output to it.

(3) In one sentence: what does "everything is a file" mean, based on what you saw?
“Everything is a file” means that Linux provides access to many system resources, including hardware devices, through a common file-like interface.




##########################################################################
The four resources the OS manages are: File, Processes, Memory and I\O.
Commands to let me see that:
File: ls -la
Processes: ps aux | head
Memory: free -h
I\O: df -h

(i\O is "devices and storage")

Command output I've found interesting:

misa@UbuntuVM:~/Desktop$ grep VmRSS /proc/$PID/status
VmRSS:	    6356 kB

why: too many for sleep process













