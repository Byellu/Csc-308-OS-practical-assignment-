Session 1 - Mutex Lock Demonstration

Objective

To demonstrate mutual exclusion using POSIX mutex locks.

Description

Multiple threads attempt to increment the same shared counter.

Without a mutex, race conditions may occur and produce incorrect results.

With a mutex, only one thread accesses the counter at a time, ensuring correct synchronization.

Concepts

- Threads
- Mutex Locks
- Shared Resources
- Race Conditions
- Critical Section

Expected Output

Each thread safely increments the counter.

Final Counter = 5