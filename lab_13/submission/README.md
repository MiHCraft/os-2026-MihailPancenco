# Lab 13 — Semaphores in Your Own Kernel

`xv6-lab13/` contains the complete source tree. `notes.txt` contains the observation answers and `terminal-output.txt` records the runs. The source is based on xv6 revision `06aad25c735fd3159bdfae5680be4eab7b1668b2`.

## Build and run

```sh
cd xv6-lab13
make qemu CPUS=3
```

At the xv6 prompt, run:

```text
semtest
mix
mix
mix lock
semtry
```

Leave QEMU with Ctrl-A followed by X.

In Ubuntu, the matching changes are staged on branch `lab-13-semaphores` in `~/os-labs-11-13-20261116/xv6-riscv`.
