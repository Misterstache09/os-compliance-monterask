**Deadlock Prevention Strategy**
I have chosen the Arbitrator approach as my deadlock prevention strategy. In my code, I initialized a counting semaphore named "waiter" to 4. Before a philosopher can pick up the chopsticks and start eating, they must first request permission from the waiter. Since the waiter only allows up to four philosophers to attempt to pick up chopsticks at the same time, this prevents a situation where all five philosophers hold one chopstick each and wait indefinitely for the other. This will ensure that at least one philosopher can pick up both chopsticks and eat, preventing deadlock.

**Compilation and Execution Instructions**
1.	Open the terminal in the directory containing the files.
2.	Compile the program using: make
3.	Run the program with: make run
4.	Delete the compiled file with: make clean
