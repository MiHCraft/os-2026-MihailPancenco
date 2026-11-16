# Lab 11 — The Race and the Semaphore

The programs ran in Ubuntu on VirtualBox using GCC 15.2.0 with `-pthread -O0`. See `terminal-output.txt` for the commands and measurements.

## Part 1 — See the race

1. An increment reads `counter` from memory, adds one to the value and writes the result back.
2. If both threads read 17 before either writes, both compute and store 18. The two increments should make 19, so one increment was lost.
3. Scheduling and progress on each CPU change which operations overlap. The observed results were 1,163,851, 1,328,231 and 1,055,195, with 2,000,000 expected. In C, concurrent plain accesses to this counter constitute a data race with undefined behavior.

## Part 2 — Mutex and semaphore

1. Both `mutex` and `sem` reached 2,000,000 on each of three runs. The mutex and the one-permit semaphore allow a single thread in the critical section.
2. With `sem_init(&s, 0, 2)`, both threads can acquire a permit at once and increment the same counter concurrently. The three results were 1,943,134, 1,939,399 and 1,948,271.
3. Each protected increment adds a synchronized acquire and release. When the threads compete, one may also wait for the other to release the lock. A timing pass measured 0.00 s for the race at the displayed precision, 0.03 s for the mutex and 0.03 s for the semaphore. The optional atomic version returned 2,000,000 in 0.01 s on the same pass.

## Part 3 — Semaphore as a signal

1. With an initial value of 1, B consumed the initial permit immediately and printed an empty string. At that point the global message array still held its initial zero bytes. A posted after writing the message.
2. With an initial value of 0, the reader must wait for a writer to post a permit before it can proceed. In that run B waited, A wrote, and B printed `hello`.

## Part 4 — Semaphore as a counter

1. The largest observed `inside` was 3. The initialization supplies three permits and `sem_wait(&places)`, before entering, requires each car to acquire one. Each departure returns one through `sem_post`.
2. At `PLACES=1` the semaphore becomes a binary lock for the parking area. The maximum observed occupancy was one. The separate mutex protects the occupancy counter and its output.
