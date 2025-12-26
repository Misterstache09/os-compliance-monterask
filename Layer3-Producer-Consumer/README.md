
This project solves the Producer–Consumer problem by using a fixed-size circular buffer controlled by three semaphores. Producers and consumers share the buffer safely, avoiding race conditions and making sure the buffer never gets too full or completely empty. The implementation is based on POSIX threads (pthread) and POSIX semaphores (sem_t).

The three semaphores used to synchronize producers and consumers are mutex, empty and full. Mutex semaphore ensures mutual exclusion when accessing or modifying the buffer and its indices. Only one thread (producer or consumer) may enter the critical section at a time. Empty semaphore tracks the number of empty slots in the buffer. Producers must wait on this semaphore before inserting an item. Full semaphore tracks the number of filled slots in the buffer. Consumers must wait on this semaphore before removing an item.


**Compilation and Execution Instructions**

Open the terminal in the directory containing the files.
Compile the program using: make
Run the program with: make run
Delete the compiled file with: make clean
