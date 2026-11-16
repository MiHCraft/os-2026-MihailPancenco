# Lab 12 — Producer, Consumer and the Other Tools

The programs ran in Ubuntu on VirtualBox using GCC 15.2.0 and `-pthread`. The terminal transcript includes the working programs and the deliberately broken variants.

## Part 1 — Bounded buffer

1. The producer waits at `sem_wait(&empty)` once all four free-slot permits are in use. The consumer releases a permit when it takes an item. The run reached four slots, consumed items 1–8 in order and returned to zero.
2. At startup the buffer is empty. The consumer waits at `sem_wait(&full)`, since `full` starts at zero. The producer may start immediately, since `empty` starts at four.
3. With the two lines swapped, the producer held the buffer mutex while it waited for an empty slot. The consumer needed that mutex to remove an item and post to `empty`. The run stopped at occupancy four and timed out with code 124. The submitted version waits on `empty` first.

## Part 2 — Condition variable

1. The mutex-protected variable `ready` remembers the state. The condition variable lets a waiter sleep and be notified when that state changes.
2. The `if (!ready)` variant printed `hello` in the observed run, as did the loop version.
3. A condition wait may wake spuriously while `ready` is still zero. The loop checks the predicate again after the wait reacquires the mutex.

## Part 3 — Readers and writers

1. The first reader takes `room` in the branch `if (++readers == 1)`; the last releases it in the branch `if (--readers == 0)`. Other readers join the group without taking `room` again. A writer needs its own permit on `room`.
2. `rlock` serializes increment, decrement and each first/last decision. Without it two readers could both act as the first, lose a count update, or release the room before the last reader left. The submitted version also prints `readers` while holding `rlock`, so the diagnostic read is synchronized. The actual reading interval still overlaps among readers.
3. If arrivals keep the readership above zero, the group retains `room` and writer 2 can starve indefinitely. In the finite run, three readers read the value 10 before writer 2 wrote 20.

## Part 4 — Circular wait

1. One holds A and waits for B. Two holds B and waits for A. The cycle is `one → B → two → A → one`. The original run returned 124 under `timeout`.
2. All ten original runs without either sleep still timed out in this VM, each after two seconds. Removing a delay can also let one thread acquire both locks first on another schedule. That would make the bug intermittent and harder to reproduce while leaving the circular dependency possible.
3. If both threads acquire A before B, no thread can wait for A while holding B, so this lock cycle cannot form. The submitted version completed both threads and returned 0.
