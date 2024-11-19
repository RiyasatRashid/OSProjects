# OSProjects
Projects I did during Operating Systems class I took in the Summer of 2024. 


Project 1:

My Project 1 code creates a parent process that copies files from one directory to two other directories by the use of pipes between it and its two offspring processes. To begin, the parent process makes two pipelines and begins the child processes. It then uses the pipes to send each child the names of the files that need to be generated as well as the contents of those files. After reading the file names and data from the pipes, the child processes create the files in the appropriate directories (d1 for child1 and d2 for child2) and write the contents that they receive into these files.
The pipe class offers input and output streams to enable inter-process communication. Through these streams, the parent process transfers the contents of the files to the child processes after reading them from the d0 directory. After receiving this data, the child processes copy the contents from d0 into d1 and d2, creating the necessary files and writing the data into them. Following the instructions for the project, this configuration enables the sharing of file contents across processes using regular pipes.

d0, d1, and d2 are sub directories while Project 1 is the directory.


Project 2:

This program models the intellectual and gastronomical journey of seven philosophers, each alternating between pondering life's mysteries and satisfying their hunger. Each philosopher operates as an independent thread, ensuring that the simulation accurately reflects concurrent real-world processes. Here's why this project stands out:

Core Features:
Concurrency with Mutex Locks:

Each philosopher uses mutex locks to "pick up" the two forks needed to eat, simulating real-life contention for shared resources.
The use of std::unique_lock ensures that resource management is handled efficiently, preventing deadlocks.
Dynamic Resource Management:

A shared resource pool represents the finite amount of food available. Philosophers only eat if resources remain, creating a real-time decision-making scenario that mirrors resource-limited environments.
Philosophical Reflection:

Before eating, each philosopher spends a randomized duration pondering life's great questions. This "thinking phase" introduces variability, ensuring the simulation isn't deterministic.
Detailed Tracking and Logging:

The program meticulously tracks and logs each philosopher's activities:
Cycle Count: How many times each philosopher alternated between thinking and eating.
Thinking Duration: Total time spent contemplating.
Eating Duration: Total time spent satisfying hunger.
The results are displayed in an engaging and personalized format, with each philosopher introducing themselves and providing a detailed account of their experiences.
Randomized Durations:

Using C++'s <random> library, the program generates dynamic and unpredictable durations for thinking and eating, adding realism to the simulation.
Graceful Exit:

Once the shared resource pool is depleted, philosophers gracefully exit the simulation, ensuring no unnecessary processing continues.
