Assignment 2
Greg Sveinbjornson
main.cpp, Makefile
Oct 4, 2022


The program parses a line of user console input
and performs the addition, subtraction, multiplication
or division of two complex numbers. The first component
in the line is either A, S, M, or D which indicates
which operation (addition, subtraction, multiplication or
division) to perform. Lowercase characters also 
work. Following the operation there are two pairs of 
floating point numbers, each pair representing a 
complex number in rectangular form. The 
character Q or q should quit the program.

The program has two different modes:

	1. Interactive mode (Receives input from command line)
	   To run this mode delete any "data.txt" file from the directory, 
	   then compile and run the program at the command line like this 
	   utilizing the make file:
	   $ make clean
	   $ make assign2
	   $ ./assign2
	    
	2. Batch mode (Receives input from an external file and write to external file)
	   To run this mode create a "data.txt" file in the directory and enter your 
	   desired inputs in it, then compile and run the program at the command line 
	   like this utilizing the make file:
	   $ make clean
	   $ make assign2
	   $ ./assign2 <data.txt> output.txt


I never got it to work on the stm chip, I just ran into way too many bugs on the
STM32CubeIDE. My logic might have been wrong I'm not sure.

