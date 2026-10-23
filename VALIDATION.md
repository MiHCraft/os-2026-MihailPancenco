# Labs 04-08: execution record

All laboratory commands and C programs were executed on **23 October 2026 inside UbuntuVM in VirtualBox**, as the ordinary user `misa`.

## Environment

- Ubuntu 26.04.1 LTS, ARM64; Linux 7.0.0-38-generic.
- GCC 15.2.0 and RISC-V GCC 15.2.0; QEMU 10.2.1.
- Existing xv6 installation: `/home/misa/xv6-riscv`, commit `06aad25c735fd3159bdfae5680be4eab7b1668b2`.
- Experiments and build logs: `/home/misa/os-labs-04-08-20261023/`.
- The original xv6 files and disk image were backed up in `backup/xv6-before.tar.gz` inside that directory before changes.

The Makefile's incorrect `$Y/_args` entry was corrected to `$U/_args`. Required sources and UPROGS entries were added to the installed checkout. Labs 04, 06 and 08 each built and booted their own xv6 image; the nested find test used another fresh image. All xv6 execution used `make qemu CPUS=1` from Ubuntu.

## Results

| Lab | Execution checks | Terminal screenshots |
| --- | --- | --- |
| 04 | sleep, shell comparison, four argv cases on both systems, executable paths, interactive keys and sh.c inspection | 10 |
| 05 | File types and devices, inodes, hard/symbolic links, directory counts, sparse files, permissions, umask, special bits, disks and /proc, two bonus experiments | 8 |
| 06 | mystat, hard links, long names, disk layout, nested find, -n, invalid paths/options and trailing slash | 5 |
| 07 | All seven programs compile with warnings as errors; ls/date/missing exec, zombie before/after wait, redirection, two-/three-stage pipes and the deliberately unclosed writer | 7 |
| 08 | Echo/ls/missing-executable variants, pingpong and the optional prime sieve | 4 |

All execution checks passed. Pipeline counts matched Ubuntu's shell: **237** for `/etc`, **231** for `/usr/bin` filtered by `grep x`. The temporary broken pipeline showed `wc -l` waiting for EOF and was terminated after observation. No zombie or broken-pipeline experiment remained running.

Lab 05 measured **umask 0002**, root filesystem **ext4 on /dev/sda2**, **19%** root usage, **6 visible logical CPUs**, and **5,360,956 KiB** of RAM. Both `/dev/null` and actual block-device nodes were visible in Ubuntu. These values describe the Ubuntu VM used for the laboratory.

## Evidence

Each submission contains its recorded `terminal-output.txt`; xv6 submissions also include `build-output.txt`. Lab 04 additionally separates its Bash and xv6 transcripts. The 34 PNG files under the report image directories are actual captures of the Ubuntu terminal. Only empty terminal margins were cropped; command text and results were not redrawn.

The LaTeX reports were updated from those measurements and captures, compiled to PDF, and rendered for layout checks. Labs 01-03, the requirement PDFs and the minimal root README were left unchanged.
