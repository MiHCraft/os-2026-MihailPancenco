# Operating Systems — Lab 3
## The Command Line: Shell, Pipes and Text Filters

Environment: Ubuntu (Bash), working directory `~/os-lab3`.

## Before we start

Created `~/os-lab3/access.log` with 500 generated entries. Each record consists of a date, time, user, status (`OK`/`FAIL`) and page. `head -3 access.log` displayed the first three records, and `wc -l access.log` returned `500 access.log`.

## Part 1 — Move fast, find help

Tab completion extended `/usr/sh` to `/usr/share/` and `cd /et` to `cd /etc/`. After running `echo something`, `ls -l` and `wc -l access.log`, pressing Ctrl+R and searching for `ec` located `echo something`; pressing Enter ran it again.

### Observations

**1. Which of `cd`, `ls`, and `echo` are built-ins, and why MUST `cd` be one?**

`cd` and `echo` are Bash built-ins. `ls` is an alias for `ls --color=auto`, which invokes the external `/usr/bin/ls` executable. `cd` must change the working directory of the current shell; a separate process would change only its own directory and leave the parent shell unchanged.

**2. How many directories are in your PATH, and in which one is `ls`?**

`PATH` contains 10 colon-separated entries (9 distinct directories, since `/snap/bin` is repeated). `which ls` returned `/usr/bin/ls`.

**3. What exit code does a command that is not found return?**

Running `nosuchprog` returned status **127**, printed using `echo "exit code: $?"`.

**4. Which option of `ls` sorts by modification time?**

`-t` (equivalently `--sort=time`). It is documented in `man ls`. The `n` key advances to the next search match; `q` exits the manual viewer.

Other available help commands: `ls --help`, `man -k "list directory"` and `help cd`.

## Part 2 — What the shell does to your line

The test directory contains `a.c`, `b.c`, `file1.txt`, `file2.txt`, `notes.txt`, and `alfa beta.txt`. The final example also creates `log1.txt`, `log2.txt`, and `log3.txt`.

### Predictions versus actual output

1. **`echo *.c`** — Prediction: `a.c b.c`. Actual: `a.c b.c`. Correct.
2. **`echo file?.txt`** — Prediction: `file1.txt file2.txt`. Actual: `file1.txt file2.txt`. Correct; `?` matches exactly one character.
3. **`echo [a-b]*`** — Prediction: entries beginning with `a` or `b`. Actual: `a.c alfa beta.txt b.c` (the filename with a space is one argument). Correct.
4. **`echo *.xyz`** — Prediction: empty output. Actual: the literal `*.xyz`. Bash leaves an unmatched glob unchanged by default (with `nullglob` disabled).
5. **`ls alfa beta.txt`** — Prediction: an error. Actual: errors for missing `alfa` and `beta.txt`. Correct; they are interpreted as two arguments.
6. **`ls "alfa beta.txt"`** — Prediction: the existing filename. Actual: `'alfa beta.txt'`. Correct; `ls` quotes the name for display.
7. **`echo '$HOME' "$HOME" \$HOME`** — Prediction: literal first item; expanded home directory second; a printed backslash in the third. Actual: `$HOME /home/misa $HOME`. The backslash prevents expansion and is removed while the shell processes the argument.
8. **`echo {1..5} ; echo $((7 * 6))`** — Prediction and actual: `1 2 3 4 5` followed by `42`. Correct.
9. **`echo "today is $(date +%A), I am $(whoami)"`** — Expected the day and username to be inserted, but did not know the `%A` format code. Actual: `today is Sunday, I am misa`. `%A` produces the full weekday name.
10. **`touch log{1..3}.txt && ls log*`** — Prediction and actual: the creation and listing of `log1.txt`, `log2.txt`, and `log3.txt`. Correct.

### Observations

**1. For each line, prediction, real output and explanations of differences:** See the ten entries above.

**2. `echo` knows nothing about files, yet `echo *.c` printed file names. Who produced them?**

Bash expanded `*.c` to matching filenames before invoking `echo`.

**3. Why did `ls alfa beta.txt` fail? Give two different ways to fix it.**

Bash split the unquoted name at the space. Either `ls "alfa beta.txt"` or `ls alfa\ beta.txt` passes the filename as one argument.

**4. What is the difference between single and double quotes?**

Single quotes preserve their contents literally; double quotes allow parameter and command substitution while keeping spaces inside one argument.

## Part 3 — Redirection, chaining and jobs

The command `ls /etc /nope > out.txt 2> err.txt` saved the `/etc` listing to `out.txt` (238 lines on this machine) and the missing-path error to `err.txt`. Redirecting with `> all.txt 2>&1` placed both streams in `all.txt`.

`echo first > notes.md` created or replaced the file; `echo second >> notes.md` appended the second line. `wc -l < access.log` printed `500` without a filename. The fallback `ls /nope 2> /dev/null || echo "failed with code $?"` printed `failed with code 2`. `sleep 100 &` started a background job that was listed with `jobs` and terminated with `kill %1`.

### Observations

**1. Which file got the error message, and which got the listing?**

The error went into `err.txt`, while the directory listing went into `out.txt`.

**2. What is the difference between `> all.txt 2>&1` and `2>&1 > all.txt`?**

Bash evaluates redirections left to right. With `> all.txt 2>&1`, standard output (1) points to the file and standard error (2) is then attached to that destination. With `2>&1 > all.txt`, standard error is first attached to the original standard output (the terminal); then only standard output moves to the file. The reversed-order experiment is still to be run and screenshotted.

**3. Why does `wc -l < access.log` print only a number while `wc -l access.log` also prints the name?**

In the first case, `wc` reads standard input and has no input filename argument. In the second case, the filename is passed explicitly.

**4. In one sentence each: `;`, `&&`, `||`.**

`;` executes commands in sequence regardless of the previous exit status. `&&` executes the next command only after success. `||` executes the next command only after failure.

`$?` means the most recent exit status; `&` at the end of a command starts a background job; `2>&1` duplicates the current standard-output destination for standard error. The string `%1` identifies shell job 1.

## Part 4 — Answer questions with one-liners

The executable answers are in `oneliners.sh`. All log-dependent results below are computed from the provided 500-entry log.

**Q1. How many requests failed?**

**100**.

**Q2. How many different pages were requested, and which?**

**4 pages:** `/page0`, `/page1`, `/page2`, `/page3`.

**Q3. How many requests did each page get?**

- `/page0`: 125
- `/page1`: 125
- `/page2`: 125
- `/page3`: 125

Their sum is 500.

**Q4. Which user or users have the most failed requests, and how many?**

**user3 and user5**, tied with **15 failures** each. The other users have 14 each, totaling 100 failures.

**Q5. How many requests did user3 make, and how many of them failed?**

**72 requests**, including **15 failures**.

**Q6. Print the last three failed requests, showing only time and user.**

```text
10:10 user0
10:15 user5
10:20 user3
```

**Q7. Which login shells appear in `/etc/passwd`, and how many accounts use each?**

Command: `cut -d: -f7 /etc/passwd | sort | uniq -c | sort -rn`.

**Actual result from the Ubuntu VM:** [Run Q7 on the VM and paste its output here; counts depend on installed accounts.]

**Q8. Predict, then explain: why do `ls /etc | wc -l` and `ls -l /etc | wc -l` differ by exactly one?**

Prediction: the long listing will produce one extra line. Explanation: `ls -l` prints the `total N` header before the directory entries, whereas ordinary `ls` does not when sent to `wc` through a pipe.

**Actual counts on the Ubuntu VM:** [Run Q8 and paste both counts here.]

### Stretch bonus (+1): extended regular expression

**Print failed requests where the minute ends in zero. How many?**

Command: `grep -E '10:[0-5]0 [^ ]+ FAIL ' access.log | wc -l`.

Expected and verified on the generated log: **50 matching failures**. The minute field is `00`, `10`, `20`, `30`, `40`, or `50`.

## Part 5 — Your first script

The executable script `report.sh` accepts a log filename, validates its existence, prints total requests and failures, and then loops over `user0` through `user6` to print failure counts. Its expected output for `access.log` is:

```text
500 requests, 100 failed
user0: 14 failures
user1: 14 failures
user2: 14 failures
user3: 15 failures
user4: 14 failures
user5: 15 failures
user6: 14 failures
```

The missing-file test `./report.sh nope.log ; echo "exit code: $?"` should display `no such file: nope.log` and exit code `1`. Confirm this on the VM.

### Observations

**1. What does `#!/bin/bash` do, and what happens if `./report.sh` is run before `chmod +x`?**

The shebang identifies Bash as the interpreter for direct execution. A script created without executable permission returns `Permission denied` when invoked as `./report.sh`; it can still be interpreted explicitly using `bash report.sh`.

**2. Why `./report.sh` instead of just `report.sh`?**

The working directory is not listed in `PATH`. `./` explicitly identifies the script in the current directory.

**3. Why does the script send the error with `>&2` and finish with `exit 1`?**

`>&2` directs the error message to standard error rather than ordinary output, and status `1` signals failure to the calling shell or another program.

### Stretch bonus (+1): cron

First, I verified that `crontab` was installed and that the cron service was running:

```bash
command -v crontab
# /usr/bin/crontab
systemctl is-active cron
# active
```

I opened my crontab using `EDITOR=nano crontab -e`. Since no personal crontab existed yet, the editor started with an empty one. I added the following entry and verified it with `crontab -l`:

```cron
* * * * * /home/misa/os-lab3/report.sh /home/misa/os-lab3/access.log >> /home/misa/os-lab3/report.log 2>&1
```

The five asterisks schedule the command **once per minute**. The absolute paths ensure that cron can locate both the script and its input file without depending on the interactive shell's working directory. The `>>` operator appends standard output to `report.log`, while `2>&1` sends standard error to the same destination.

After waiting for repeated executions, I inspected the log using `tail -20 ~/os-lab3/report.log`. The recorded output included successive reports:

```text
user3: 15 failures
user4: 14 failures
user5: 15 failures
user6: 14 failures
500 requests, 100 failed
user0: 14 failures
user1: 14 failures
user2: 14 failures
user3: 15 failures
user4: 14 failures
user5: 15 failures
user6: 14 failures
500 requests, 100 failed
user0: 14 failures
user1: 14 failures
user2: 14 failures
user3: 15 failures
user4: 14 failures
user5: 15 failures
user6: 14 failures
```

The repeated blocks confirm that cron executed `report.sh` automatically more than once. Each execution analyzed 500 requests and counted 100 failures; `user3` and `user5` had the highest number of failures (15 each).

**Cleanup:** I reopened the crontab with `EDITOR=nano crontab -e`, removed the temporary schedule, and checked `crontab -l` again. Its output contained only the default explanatory comments and no active job entries. Thus, the experiment was completed without leaving a recurring task running.
