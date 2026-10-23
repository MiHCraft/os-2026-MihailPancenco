# Lab 08

Sources target the xv6-riscv checkout installed in UbuntuVM, commit `06aad25c735fd3159bdfae5680be4eab7b1668b2`. The complete Makefile retains earlier lab utilities and adds the programs required by this lab.

Copy `user/*.c` into `~/xv6-riscv/user/` and merge the matching UPROGS entries from `Makefile` into the xv6 root Makefile. Each entry starts with a TAB and ends with a backslash. A checkout containing all earlier sources can use the supplied Makefile directly.

```sh
cp ../../lab_04/submission/user/*.c ~/xv6-riscv/user/
cp ../../lab_06/submission/user/*.c ~/xv6-riscv/user/
cp user/*.c ~/xv6-riscv/user/
cp Makefile ~/xv6-riscv/Makefile
cd ~/xv6-riscv
make clean
make qemu CPUS=1
```

Quit QEMU with Ctrl-A, then X. `notes.md` contains the observations, `terminal-output.txt` the recorded Ubuntu/xv6 session and `build-output.txt` the compiler output. The sibling report directory contains the LaTeX report, terminal screenshots and PDF.
