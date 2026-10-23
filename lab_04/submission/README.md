# Lab 04: build and run

Source baseline: MIT xv6-riscv commit `f780d7850765d74cbdcd1fff4b822d8829f7c9bd` (branch `riscv`). This submission contains the complete upstream Makefile with the lab programs added to `UPROGS`, and the required sources under `user/`.

From this submission directory, install the files into your existing xv6 checkout:

```sh
cp user/*.c ~/xv6-riscv/user/
```

For a checkout at the recorded baseline, copy `Makefile` to the xv6 root. If your checkout has changes from previous labs, keep its Makefile and merge these entries into its existing `UPROGS` block instead:

```make
	$U/_sleep\
	$U/_args\
```

Each entry starts with a literal TAB; the backslash is the last character on the line. Do not build this standalone submission directory: it is an overlay for the full xv6 tree.

```sh
cd ~/xv6-riscv
make clean
make qemu
```

Quit QEMU with Ctrl-A followed by X. Read `notes.md` for experiments and expected interpretations. The full LaTeX report and compiled PDF are in `../report/`.
