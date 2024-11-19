# OSProjects
Projects I did during Operating Systems class I took in the Summer of 2024. 


Project 1:

My Project 1 code creates a parent process that copies files from one directory to two other directories by the use of pipes between it and its two offspring processes. To begin, the parent process makes two pipelines and begins the child processes. It then uses the pipes to send each child the names of the files that need to be generated as well as the contents of those files. After reading the file names and data from the pipes, the child processes create the files in the appropriate directories (d1 for child1 and d2 for child2) and write the contents that they receive into these files.
The pipe class offers input and output streams to enable inter-process communication. Through these streams, the parent process transfers the contents of the files to the child processes after reading them from the d0 directory. After receiving this data, the child processes copy the contents from d0 into d1 and d2, creating the necessary files and writing the data into them. Following the instructions for the project, this configuration enables the sharing of file contents across processes using regular pipes.

d0, d1, and d2 are sub directories while Project 1 is the directory.
