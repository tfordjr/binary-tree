binary-tree
GitHub Repo: https://github.com/tfordjr/binary-tree/
CS 4280 P0 - Terry Ford Jr. - 09/23/2023

Important Files:
tree.c Handles args, generates binary trees, and generates output files via fileOutput().
tree.h Binary Tree header file with nodes that each have an char* array to hold strings of the same length. 
tree.h also has options to print binary tree either to stdout or to a file.
Makefile that simply generates tree.c as P0, also has make clean that deletes all output files and executables.
names.f23 data file that has input of variable length strings, some repeated, \n \t and whitespace characters.

Invokation:
Can invoke with three different methods
./P0   - This method will rely on stdin from keyboard until ^D (ctrl+D) EOF signal recieved
./P0 < names.f23  - This method feeds a given file through stdin
./P0 names    - This method appends .f23 to given arg and accesses names.f23 and uses that input
providing more than one arg will result in the termination of the program.

Regardless of input method, the given input strings will be used inserted into a binary tree. 
From this binary tree, three output files will be generated for the output of the binary tree in pre, post, and inorder.

