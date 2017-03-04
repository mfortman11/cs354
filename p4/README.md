Overview

The purpose of this assignment is to understand more about how caches work, learning a bit about simulation along the way, and picking up introductory skills in generating a Makefile.

Please read this entire assignment specification before starting on the first step.

Description

For this assignment, you will use a program called pin that produces cache performance statistics, given cache parameters and an executable.

pin runs the executable to internally produce a series of address traces. These are the ordered set of addresses that a program generates as it runs. They represent the addresses read from or written to as the program runs. Each address may represent a read for the instruction fetch or a read or write to a variable stored in memory.

The address traces are then used internally with a cache simulator. The cache simulator is a program that acts as if it is a cache, and for each trace, does a look up to determine if that address causes a cache hit or a cache miss. The simulator tallies the hits/misses, and when it has completed simulation of all the traces, it prints these statistics for you.

To run a simulation, use a command line similar to

/p/course/cs354-common/public/cache/pin -t /p/course/cs354-common/public/cache/source/tools/Memory/obj-ia32/allcache.so -is 16384 -ia 1 -ib 64 -ds 16384 -da 1 -db 64 -- yourexe
The first time you run this command, you should probably copy, paste, and then alter this command, instead of typing it in, to reduce errors. The arrow keys on your keyboard can be your friend here, before you generate a Makefile. Once you put a target for this command line into your Makefile, your life gets easy!
6 of these command line arguments specify cache parameters to pin. The simulator presumes separate I-cache and D-cache. The I-cache holds only the machine code instructions, as read when doing an instruction fetch. The D-cache holds all other data read or written while a program runs.

For the I-cache, specify

-ia 1 
This causes the set associativity of the cache to be 1, or direct mapped. This is the only value we will use in this assignment.
-is N 
Substitute a power of 2 for N. This sets the capacity for this cache. For all our simulations, use a 16KiB size.
-ib N 
Substitute a power of 2 for N. N is the number of bytes per block.
For the D-cache, specify

-da 1 
This causes the set associativity of the cache to be 1, or direct mapped. This is the only value we will use in this assignment.
-ds N 
Substitute a power of 2 for N. This sets the capacity for this cache. For all our simulations, use a 16KiB size.
-db N 
Substitute a power of 2 for N. N is the number of bytes per block.
As you work your way through this assignment, you will be answering questions that are in the file:

   /p/course/cs354-common/public/html/handouts/a4questions
Copy this file to your own directory, and add your answers to this file. The file will be turned in.

Step One: 1-dimensional array code

Write a very small C program called cache1D.c that sets each element of an array of 100,000 integers to the value of its index. The statement that sets a single array element will be something like

  arr[i] = i;
The resulting executable program will be used with pin to generate statistics about cache usage for your analysis. To make the analysis easier, the C program is required to
Declare the array as a global variable, so the declaration will be outside of main() (and prior to main() within the source code file). This requirement will cause the array to be within the global data segment, and not on the stack.
Place a for loop inside main() to set each element of the array. One array element is set during each iteration of the for loop.
Compile your program with

  gcc -o cache1D cache1D.c -Wall -m32
Notice that this command differs slightly from the compilation that we did for assignment 1 this semester. It does not have the -O option, so the compiler is not going to do optimizations. Use these same compiler options for all the programs in this assignment.

Before you go any further, it is time to figure out how to do this compilation using make: a powerful tool that helps us to automate our compilation, as well as automate many other sets of commands.

To help you put together a Makefile, try one or more of

A brief tutorial about make by Hector Urtubia can start you on your way.
Within the online textbook written by our own Arpaci-Dusseau professors, see the Laboratory: Tutorial. You'll benefit from pages 1-8 of this tutorial, although pages 5-8 specifically discuss make.
University of Maryland has a nice introduction to make; especially helpful will be to look at the topic of dummy targets. You will want to add a dummy target for each of your simulations.
UW-Madison alumni Professor Newhall explains using make in helpful and concise prose. in a
Make sure that you have a single target to make the cache1D executable. (And for each subsequent program, add a new target, and then use make. You will be turning in your Makefile. Please name your target with the name of the executable, which should be the same as your source code, but without the .c file name extension.)

Decide upon a strategy to test that your code works. Then, make a copy of cache1D.c and implement your strategy to test your code on the copy. You will not turn in this copy, but you will have to describe your strategy.

Step Two: 1-dimensional array code analysis

Run the 3 simulations needed to answer the questions in the a4questions file. Then, answer the questions. Running the simulations will be amazingly easy, if you put a target for each block size simulation into your Makefile! So, do it!

Step Three: 2-dimensional arrays, two ways

Repeat what you did for the 1 dimensional array with two programs that set elements of a 2-dimensional array. Many students will not have used 2-dimensional arrays in C before; the K&R book, section 5.7-5.9, starting on page 110 will be a good reference for declaring and using 2D arrays.

First, write a C program called cache2Drows.c that sets each element of a 3000 row by 500 column array of integers to the sum of the row index and the column index. The statement that sets an element will be something like

  arr2d[row][col] = row + col;
Use a set of nested for loops, where the inner loop works its way through a single row of the array, and the outer loop iterates through the rows.
Decide how you will test that your code works, and test it (on a copy of the source code).

Run the cache analysis requested in the a4questions file.

Second, write another C program called cache2Dcols.c that does the same thing as cache2Drows.c did, but in a different order. This program has the inner loop work its way through a single column of the array, and the outer loop iterates through the columns. If you truly understand your code, it should be close to trivial to copy cache2Drows.c and modify it to become cache2Dcols.c.

Again verify your code (on a copy of the source code), and run the cache analysis for this program, as specified in the a4questions file.
Last step will be to figure out, understand, and explain why these 2 programs (that accomplish exactly the same thing) result in different cache performance.
