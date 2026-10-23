# Lab 08 - The Same Calls, Inside Your Own OS

## Environment and evidence

Compiled and executed on 23 October 2026 with MIT xv6-riscv commit `f780d7850765d74cbdcd1fff4b822d8829f7c9bd`, the RISC-V GNU compiler and QEMU. The recorded session used one emulated CPU and a combined image of the lab 04, 06 and 08 programs. Each submitted Makefile also built independently. The terminal blocks are recorded output, and `terminal-output.txt` contains the full session. PIDs and executable listings depend on the run.

## Part 1 - run inside xv6

`user/run.c` preserves the supplied lab's program. The parent prints its PID and forks. The child prints its own PID, builds a NUL-terminated array of strings, and calls `exec("echo", args)`. The parent calls `wait(&status)` and reports the child's status. The Makefile includes `run` in `UPROGS`.

```text
$ run
parent: my pid is 57
child: my pid is 58
hello from the child
parent: child 58 ended with status 0
```

### The ls and missing-program variants

`user/runls.c` changes the child's array to `{ "ls", 0 }` and executes `ls`. `user/runmissing.c` changes the executable pathname to `nosuchprog`, which deliberately fails. Keeping separate variants allows the default `run` program to remain exactly the echo example and lets the assistant run all cases without editing a source file.

Recorded `runls` output, with its long directory listing shortened:

```text
$ runls
parent: my pid is 59
child: my pid is 60
.              1 1 1024
..             1 1 1024
[remaining directory entries omitted]
parent: child 60 ended with status 0
```


```text
$ runmissing
parent: my pid is 61
child: my pid is 62
exec failed
parent: child 62 ended with status 1
```

### 1. Compare the three calls with Linux

| Operation | xv6 lab 08 | Linux lab 07 |
| --- | --- | --- |
| Create the child | `fork()` | `fork()` |
| Replace the child image | `exec("echo", args)` | `execlp("ls", "ls", "-l", (char *)NULL)` |
| Reap the child | `wait(&status)` | `waitpid(pid, &status, 0)` |

The lifecycle is the same: fork creates a separate process with inherited descriptors and memory contents; exec replaces the child image while retaining its PID; wait synchronizes with termination and reaps it. Linux `execlp` is a libc helper with PATH search and a variadic argument list. xv6's `exec` takes an explicit pathname and argument vector and does no PATH search. xv6 `wait` waits for a child and stores the exit value directly; Linux waitpid can select a child and returns an encoded status decoded with wait macros.

### 2. Who prints hello from the child

The `echo` program prints it. Before exec, `run` prints only the parent and child PID messages. Successful exec never returns to the old program; the new echo image uses the supplied argument strings to produce `hello from the child`.

### 3. Why the failure statuses differ

The xv6 branch after failed exec explicitly calls `exit(1)`, so its parent prints status 1. The Linux branch explicitly calls `exit(127)`, so its parent prints 127 after decoding it. The values were chosen by the programs; exec itself returns an error to the caller instead of automatically deciding this exit status. The xv6 parent still exits 0 after reporting its child, as in the supplied example.

## Part 2 - pingpong

`user/pingpong.c` creates two pipes, `p2c` and `c2p`. The child closes `p2c[1]` and `c2p[0]`; the parent closes `p2c[0]` and `c2p[1]`. The parent initializes the byte to `p`, writes it to the first pipe, and waits in a read on the second pipe. The child reads the byte, prints its ping message, writes the byte back, closes its descriptors and exits. The parent receives the reply, prints pong, closes descriptors and reaps the child.

```text
parent p2c[1] -- one byte --> p2c[0] child
parent c2p[0] <-- one byte -- c2p[1] child
```

```text
$ pingpong
64: received ping
63: received pong
```

The actual child PID is 64 and the parent PID is 63. The order is guaranteed by the code: the child prints ping before writing the reply, and the parent prints pong only after receiving it. Scheduler timing may delay either process, but cannot reverse these messages in a successful exchange. Pipe, fork, read, write and wait errors are checked; a failed exchange exits nonzero.

### 1. Why two pipes

A pipe is a one-way byte stream. Using a separate pipe per direction gives each process an unambiguous input and output channel. If both processes read and write a single shared pipe, either can consume its own byte because a pipe does not address messages to particular readers. Two pipes implement the required reliable round trip without that race.

### 2. Which call waits for the reply

The parent's `read(c2p[0], &b, 1)` blocks while there are no bytes available and a writer remains open. The child writing its reply makes that read complete. The later `wait(&status)` reaps the child; it is not what makes the parent wait for the reply byte. Closing unused write ends also ensures a failed/exited peer can produce EOF rather than leaving a reader blocked indefinitely.

## Optional - Prime sieve

`user/primes.c` generates integers 2 through 35 and builds a process chain. Each filter reads its first integer as a prime, prints it, and forwards only integers not divisible by that prime through a new pipe to its child. Reads and writes transfer one integer at a time. Every process closes inherited unused ends and its output end when input reaches EOF, then waits for its child. The empty final stage exits without printing.

```text
$ primes
prime 2
prime 3
prime 5
prime 7
prime 11
prime 13
prime 17
prime 19
prime 23
prime 29
prime 31
```

The output matches all eleven primes in the inclusive interval 2 through 35. Closing the final writers propagates EOF through the chain so all filters can exit. Keeping only necessary descriptors also stays within xv6's per-process descriptor limit.

## Submission checklist

Required: `user/run.c`, `user/pingpong.c`, the complete xv6 `Makefile`, and this `notes.md`. Also included: `user/runls.c`, `user/runmissing.c`, optional `user/primes.c`, build instructions and the terminal transcript. All five sources have matching `UPROGS` entries. The report directory contains the LaTeX report and compiled PDF.
