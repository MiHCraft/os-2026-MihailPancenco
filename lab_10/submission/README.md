# Lab 10 — Add Your Own System Call: trace

- `xv6-lab10/` contains the complete xv6 source tree with `trace` and the optional `sysinfo`.
- `notes.txt` records the mask experiments.
- `terminal-output.txt` and `build-output.txt` contain the terminal results and build logs from Ubuntu in VirtualBox.

## Build and run

```sh
cd xv6-lab10
make qemu CPUS=1
```

Run `trace 32 grep hello README`, `trace 2 usertests forkforkfork` or `sysinfo` at the xv6 prompt. Press Ctrl-A then X to leave QEMU.
