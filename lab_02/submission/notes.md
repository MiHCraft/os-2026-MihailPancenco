# Operating Systems — Lab 2

## Meet the OS You Will Build

### Part 2: Use xv6 as the Unix it is

#### 1. List three programs xv6 ships with

xv6 includes several standard Unix utilities, including `cat`, `echo`,
and `grep`. These programs are available directly from the xv6 shell.

#### 2. You just used a pipe (`|`) inside xv6. Which two OS features must exist for a pipe to work?

A pipeline requires process management and inter-process communication (IPC).
The operating system must support the execution of separate processes and
provide a pipe through which one process can send data to another.

#### 3. In one sentence: how does the xv6 shell compare to the Linux shell from Lab 1?

The xv6 shell supports familiar Unix commands and pipelines, but provides
fewer utilities and features than a modern Linux shell.

---

### Part 3: Read the source

#### 1. Which system calls does user/cat.c use, and what does each one ask the kernel to do?

The `cat()` function uses the following system calls:

- `read()` — reads bytes from an input file descriptor into a buffer.
- `write()` — writes the contents of the buffer to standard output.
- `exit()` — terminates the process when an error occurs.

The complete program also uses:

- `open()` — opens an input file and returns its file descriptor.
- `close()` — releases a previously opened file descriptor.

These operations allow `cat` to read data from files or standard input
and display it through standard output.

#### 2. In which kernel file, and on which line, is sys_read implemented?

The `sys_read()` function is implemented in `kernel/sysfile.c`,
beginning at line 69.

The corresponding `sys_write()` function begins at line 83
of the same file.

#### 3. In one sentence: what is the difference between the code in kernel/ and the code in user/?

The `kernel/` directory contains privileged operating system code
responsible for managing system resources, while `user/` contains
ordinary programs that access these resources through system calls.