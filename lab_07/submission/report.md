# Lab 07 - Three Small Programs: Processes, Redirection, a Pipe

## Environment and evidence

Built and tested on 23 October 2026 in Debian GNU/Linux, ARM64, as non-root user `student`. The Makefile builds with C11, `-Wall -Wextra -Werror`. The terminal blocks below come from actual runs. PIDs, dates, file listings and directory counts vary across machines. Complete captured output is in `terminal-output.txt`. The programs were tested in a temporary Linux container; they can also be compiled with the individual gcc commands from the handout.

```sh
make
# Or, for example:
gcc -Wall -Wextra -o run run.c
```

## Part 1 - fork, exec and wait

`run.c` preserves the supplied lab program: the parent prints and flushes its PID, forks, the child prints its PID and parent PID, then uses `execlp` to become `ls -l`. The parent waits with `waitpid` and decodes the child's termination status. The explicit flush before fork prevents a buffered parent message from being duplicated when stdout is captured.

The two required one-line variants are kept as separate source files, `run_date.c` and `run_missing.c`, so all three behaviors remain reproducible without editing the final working `run.c`.

Actual `run` output, with the directory listing shortened:

```text
$ ./run
parent: my PID is 8781
child:  my PID is 8782, my parent is 8781
total 536
[directory entries omitted]
parent: child 8782 ended with status 0
```


```text
$ ./run_date
parent: my PID is 8783
child:  my PID is 8784, my parent is 8783
Fri Oct 23 09:38:56 UTC 2026
parent: child 8784 ended with status 0
$ ./run_missing
parent: my PID is 8785
child:  my PID is 8786, my parent is 8785
exec: No such file or directory
parent: child 8786 ended with status 127
```

### 1. Why perror runs only after a failed exec

A successful `execlp` replaces the child's process image and never returns to the following line. The same PID now runs the new program. If exec fails, it returns -1 and sets errno; only then does `perror("exec")` execute. The missing-program variant deliberately exits with 127 after printing its error.

### 2. Whose PID is printed as my parent

The child prints 8781 as its parent in the recorded `run` experiment, the PID printed by the original parent process. `getpid()` returns the calling process's own ID; `getppid()` returns its current parent's ID. Here the parent stays alive and waits, so the child is not reparented during this observation.

### 3. Exit statuses

The parent reports 0 for successful `ls` and `date`, and 127 for `nosuchprog`. These are the child's exit statuses. The supplied parent program itself returns 0 after reporting them, including the missing-program experiment; this differs from the child status it prints. Linux waitpid returns an encoded wait status, so `WEXITSTATUS` extracts the exit value when the child exited normally. A general shell would also handle signal termination using `WIFEXITED`/`WIFSIGNALED`.

## Part 2 - A zombie, on purpose

`zombie.c` is the `ls` version of `run.c` with `sleep(20)` immediately before `waitpid`. The test started it in the background, inspected its child after two seconds, then waited for the parent to finish.

```text
$ ps -o pid,ppid,stat,cmd -p 8803,8804
PID  PPID STAT CMD
 8803  8776 S    ./zombie
 8804  8803 Z    [ls] <defunct>
$ ps -o pid,ppid,stat,cmd -p 8804
PID  PPID STAT CMD
```

### 1. The Z state

The child's STAT letter is `Z`, meaning zombie: `ls` has exited, but the kernel retains its PID and termination status until its parent reaps it. It is not running useful code or sleeping to finish its work. The parent's `S` means sleeping.

### 2. What removes the zombie

After the parent wakes from its 20-second sleep, `waitpid(pid, &status, 0)` consumes the child's recorded exit information and removes its process-table entry. The second `ps` has only the header for that PID. The elapsed sleep alone does not reap a child; the wait call does.

## Part 3 - Output redirection

`redirect.c` forks, closes descriptor 1 in its child, opens `out.txt` with `O_WRONLY | O_CREAT | O_TRUNC` and mode 0644, then execs `ls -l`. The parent retains its terminal/capture stdout and waits. The program checks fork/open/exec/wait errors and reports the child result.

```text
$ ./redirect
open gave descriptor 1
done: the listing is in out.txt
```

`out.txt` was also checked to begin with the `total` header of a long directory listing. It is generated when the program runs, rather than submitted as a machine-specific listing.

### 1. Why open returned 1

`open` chooses the lowest unused descriptor. Standard descriptors 0, 1 and 2 were initially open; closing 1 made it the first free slot. The recorded diagnostic confirms that open returned 1. This experiment relies on the normal standard-descriptor setup.

### 2. Why unchanged ls writes to the file

`ls` still writes to descriptor 1. The forked child's descriptor table was modified before exec, and descriptors remain open across exec unless marked close-on-exec. Consequently `ls` inherits stdout pointing at `out.txt`. The diagnostic is sent to descriptor 2 and remains visible; the parent's final message also remains visible because descriptor changes were made only in the child.

### 3. Redirecting errors

For `2> err.txt`, close descriptor 2 before opening the error file, leaving descriptors 0 and 1 open so the file gets 2. A general implementation can use `dup2(fd, STDERR_FILENO)` to select the target explicitly. Descriptor 2 is standard error; descriptor 1 is standard output.

## Part 4 - A pipe

`pipeline.c` creates a pipe and forks two children. The producer closes stdout and duplicates the write end onto descriptor 1, then execs `ls /etc`. The consumer closes stdin and duplicates the read end onto descriptor 0, then execs `wc -l`. Each child closes both original pipe descriptors after duplication. The parent closes both ends and waits for both specific children.

```text
$ ./pipeline
112
$ ls /etc | wc -l
112
```

### 1. Comparison with the real shell

Both counts are 112 in the recorded environment. This equality, rather than the particular count, verifies the connection. `ls` writes one filename per line when its output is a pipe, and `wc -l` counts those lines.

### 2. Which child hangs after leaving a writer open

The experiment commented out only the parent's final `close(p[1])` in a temporary copy, compiled it and inspected it. The submitted `pipeline.c` remains the working version. The temporary program was still running after one second:

```text
$ ./broken (parent write end left open)
PID  PPID STAT CMD
 8812  8776 Ss   /tmp/tmpeiiz8bal/broken
 8814  8812 S    wc -l
Still running after 1 second; stopped by test harness.
```

`ls` had already exited; `wc -l` was still sleeping. The test stopped the temporary process group after the observation, equivalent to interrupting the foreground pipeline with Ctrl-C.

### 3. What wc is waiting for

`wc` is waiting for EOF: after buffered bytes are consumed, read returns EOF only when every descriptor referring to the pipe's write end is closed. The parent's unused open writer keeps that condition false, while the parent waits for `wc` to exit. Pipe end closure is part of the communication protocol, not just resource tidiness.

## Optional - Three stages

`pipeline3.c` implements `ls /usr/bin | grep x | wc -l` using two pipes and three children. The first child redirects stdout, the middle child redirects both stdin and stdout, and the last redirects stdin. Every child and the parent close all four original pipe descriptors after the required duplicates.

```text
$ ./pipeline3
106
$ ls /usr/bin | grep x | wc -l
106
```

Both methods returned 106. The parent waits for every created child and reports a nonzero result if one fails. The optional source is included alongside the required programs.

## Submission checklist

Required: `run.c`, `zombie.c`, `redirect.c`, `pipeline.c`, and this `report.md`. Also supplied: `run_date.c`, `run_missing.c`, optional `pipeline3.c`, a Makefile, and the complete terminal transcript. `make clean` removes generated executables and `out.txt`. The separate report directory contains the LaTeX report and compiled PDF.
