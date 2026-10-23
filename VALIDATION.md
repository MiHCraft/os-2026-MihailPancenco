# Labs 04-08: validation record

Validation date: **23 October 2026**. The existing labs 01-03 and all teacher requirement PDFs were left unchanged.

## Environments

- Linux: Debian GNU/Linux 12 (bookworm), ARM64, in a temporary Docker Desktop container on macOS; the permission experiments ran as non-root `student` with umask `0022`.
- Linux compiler: GCC 12.2.0, using `-std=c11 -D_POSIX_C_SOURCE=200809L -Wall -Wextra -Werror -O2` for lab 07.
- xv6: official MIT xv6-riscv commit `f780d7850765d74cbdcd1fff4b822d8829f7c9bd`; GCC RISC-V cross compiler 12.2.0 and QEMU 7.2.22.
- The xv6 behavioral transcript uses a combined image of labs 04, 06 and 08 with `CPUS=1`. Each submitted Makefile also produced its own filesystem image independently.
- Reports: compiled locally with pdfLaTeX; rendered to images and checked for layout and readable terminal/source blocks.

## Checks and results

| Lab | Checks | Result |
| --- | --- | --- |
| 04 | sleep with and without argument; all command-line Bash comparisons; all four argv examples on Linux and xv6; source inspection of sh.c | Passed. Redirection printed `hello`; LIST was verified to call wait before its right command. |
| 05 | File types, links, sparse files, chmod, umask, directory read/search, special bits, disk and /proc queries; gzip signature and open-unlinked-file bonus experiments | Recorded real output. The non-root permission denials and link-count changes matched the explanations. |
| 06 | mystat for multiple paths and missing paths; hard links and unlink; long names; mkfs layout; nested find, directory match, trailing slash, missing path, bad option and -n | Passed. Three `r2` paths were found; only the root hard link shared cat's inode. |
| 07 | All seven Linux programs compile with warnings as errors; ls/date/missing exec; zombie before and after wait; redirected file; two-/three-stage pipeline counts; deliberately unclosed parent writer | Passed. Counts matched the shell (112 and 106). The zombie was reaped; the broken pipeline left wc waiting and was stopped by the harness. |
| 08 | Echo, ls and missing-executable run variants; pingpong byte round trip; optional prime sieve | Passed. Ping preceded pong; primes were 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31. |

The submitted normal programs remain working versions; the deliberately broken pipe variant was compiled only in a temporary directory. Generated Linux executables and `out.txt` were removed after checking.

## Interpretation limits

Lab 05 records the available Linux VM/container, not a native Ubuntu installation on the student's laptop. Its root mount is overlay; ext4-backed `/dev/vda1` appears through bind-mounted configuration files. The block-device nodes are not exposed in the container's `/dev`, so the report documents this visibility limit instead of inventing a `b`-type listing. Disk fullness, visible logical CPUs and RAM must be interpreted in that environment. `collect.sh` can collect corresponding values on another Linux installation.

Lab 04's interactive Bash history/completion facilities are explained from the shell behavior; the automated comparison did not simulate interactive keypresses. Complete terminal records are supplied separately from abbreviated report excerpts. PIDs, inode assignments, file sizes, timestamps and directory counts are run-specific.

## Deliverable locations

Required C files for xv6 are under `lab_04/submission/user/`, `lab_06/submission/user/` and `lab_08/submission/user/`, matching the handouts. Linux C files are directly under their submission directory. Each lab contains its required `notes.md` or `report.md`, and each report directory includes editable LaTeX and `main.pdf`.
