Overview

The purpose of this program is to quickly become good at writing C programs, gaining the experience of working in a non-object oriented language. Arrays, command-line arguments, file I/O, pointers, and structures are used.

Program Description

This project has lots of little details to get right, learning those details along the way. You will write 3 C programs. To begin with, you are given the program generate. Running this program generates a set of integers.

The representation of an integer is a key point of understanding in this assignment. If we have 8-bit two's complement integers, then the representation for the value 12 is (given in binary) 00001100. If we use a C string, then there are 3 8-bit ASCII characters to represent the C string "12" (given in binary):

     00110001 00110010 00000000
The generate program writes two's complement integer representations to a file; this representation is often called binary output. It also prints out the ASCII version of the integers to stdout (the display), placing each value on its own line.
You will be writing programs that work with two types of files: binary and ASCII. It is important to know which type of input or output you are working with.

Step 1: Use The Tools

To get yourself warmed up, first make a directory where you will be working in your CS account. Probably best to do this in your private/ directory, which has permissions set such that no one else can easily access your files. Like this:

    shell% cd private/
    shell% mkdir cs354
    shell% cd cs354
    shell% mkdir p1
    shell% cd p1
The above sequence changes directories (using the cd command) into your private directory, creates a new directory (sometimes called a folder) called cs354 inside of the private directory, and then makes a new directory for this project called p1, and finally changes to that new directory.

Copy the file generate.c into your directory. This file is located in the directory:

  /p/course/cs354-common/public/html/homeworks/
Compile the program with the following command:

    shell% gcc -o generate generate.c -Wall -m32 -O
That last command line argument is the capital letter O. It is not the digit zero (0).

At this point, you should have an executable program. To run it, type:

    shell% ./generate ints-file
Note that shell% above is called the shell prompt, and may be different for the shell you are using.

If you have done everything correctly, running the program should create a file named ints-file containing a set of 32-bit two's complement integers. For each integer written to the file, it was also printed to stdout, which comes to the display window. The output to the display window are ASCII characters.

To introduce the concept of shell redirect, alter the shell command such that output sent to stdout instead is captured in a file:

    shell% ./generate ints2-file > ascii2-file
To try to see the results of your work, you might try the shell command:

    shell% cat ints2-file
The cat program is a standard Unix tool for displaying text (ASCII) files. The goal is to understand why what you see is not what you might initially expect.

Also try cat with the file ascii2-file. Look at the source code for generate to see what is different. Before continuing on with this assignment, you should be able to explain why the output of cat is different for these two files.

Note that for this assignment, all the sample file names are devised to distinguish their contents. Names with ints in their name have binary contents, and names with ascii in their name have ASCII contents. Unlike Windows systems, Unix (Linux) systems give no meaning to file name extensions, so we don't need them.

On purpose, to show you some variety in programming style, the generate program uses the assert library to verify the return values from functions. Doing this likely requires less code to handle program errors, but you also have less control over what happens when the program asserts on an error. Users of the program will likely not understand the displayed error messages without also knowing and understanding your source code. You can accomplish the same task without the extra library inclusion by using if statements to make sure that return values are what they should be.

Step 2: Average the Integers

Time to write some code. Write a C program called stats.c that reads integers from a binary file of integers, and computes the integer average of those integers.

This very simple program is to be written in a specific way to give you extra programming practice, and to expose you to some concepts. Follow this specification, as alternative implementations will receive score deductions.

The integers are read one at a time from a file given as a command line argument. Each integer is placed into an array of integers as it is read. Note that if the user invokes the stats program incorrectly (say, without an argument, or with two or more arguments), the program should print an error message and call exit(1).

An array of exactly the right size is to be allocated dynamically by using the malloc() function. malloc() needs the number of bytes it is to allocate as its parameter. The fstat() call can be used to figure out the size of the file.

After reading all the integers from the file and placing them into the array, close the file.

After closing the file, compute the integer average of the values in the array, and print both the count of the number values averaged and the average.

To write this program, you will use a set of library functions. Using library functions is something you will do a lot when writing programs, and each library function is fully specified in a manual page. So, to learn about the function, read the manual page. The library functions that will be used for this program are

open() to open the file
fstat() to get statistics about the file
malloc() to allocate the array of integers
read() to read each individual integer
close() to close the file when done
printf() to display results to the screen
To learn more about these functions, read the man pages! There's a Unix command for that. Run

    shell% man printf
or
    shell% man 2 open
    shell% man 2 read
    shell% man 2 close
The number two is required above to get the right version of the manual page. Section 2 of the man pages is for system calls, which are calls to the operating system for service of some kind.
In your implementation, make sure to always check the return value of functions. If the file cannot be opened, then the program should not read input. If the read fails, then the program should detect the failure and do something relevant. Points will be deducted for forgetting to check return values.

When opening a file for reading, it only needs a O_RDONLY flag. Read the man pages of these calls carefully to see how to open, read, and close a file correctly.

This program should work with any input file of binary values. The quantity of integers can vary. So, you will want to consider how you can test your program with a variety of input files. Certainly, when your program is being graded, the input file will not be the same one you produce with the generate program you've been given.

Step 3: Play a little guessing game

Time to write a program that is not quite trivial. Write a C program called game.c that reads the integers from a binary file and builds a singly linked with them. Then, the program repetitively asks the user to guess an integer that might be in the list. The user enters a guess, and the program searches the linked list to either find the integer or not. It prints a message as to whether it found the integer or not.

A program run should look like this, where the user input is in bold:

 % game  ints-file
 This game has you guess which integers are in the list.
 Enter an integer (followed by the newline)
 or q (followed by the newline) to quit.
 Integer guess: 25
 25 is not in the list.
 Integer guess: 0
 0 is in the list.
 Integer guess: abq
 0 is in the list.
 Integer guess: -12
 -12 is not in the list.
 Integer guess: -1
 -1 is in the list.
 Integer guess: q
For this program, you are given a set of functions to write. This will organize your code for you, as well as give you practice handling functions in C. Follow this specification, as alternative implementations will receive score deductions.

There are two development steps to this program. The first step is to build the linked list. Get this part of the program completely working before tackling the second step. From the stats program, you already have written code that opens a file and reads 1 integer at a time from that file. Reuse that code! The difference with this program is that instead of placing the integers into an array, the program adds each integer to a singly linked list. Building and using this linked list will give you experience with structures and with using pointers.

Some details about the linked list:

A pointer to the first node in the list identifies where the list is; it is called the head of the list. If the head has the value NULL, then the list is empty. There are no nodes in the list.
Since we do not care about the ordering of the list, add each new node (integer) to the front of the list. This is the easiest (and most efficient) code to write. (You should be able to explain why this is more efficient than adding a new node to the tail end of the list.)
It is not required, but it will be good experience, and it will help you to test your code, if you write a function that iterates through the linked list, printing out each value on its own line. The head of the list is passed as a parameter.

Organize this first part of the program by implementing these functions:

Node * createlist(int fd); 
This function receives the file descriptor of an already successfully opened file. It then reads one integer at a time from that file, and for each integer, calls listadd, which will add the integer to the list. It returns the head of the list once the list has been made. If something goes wrong, or if the list is empty, it returns the value NULL.
Node * listadd(Node *head, int intforlist); 
This function creates a new Node structure, and hooks it into the list. It is not required, but it is highly recommended to add the new node to the front (head) of the list. This function returns the (new) head of the linked list.
Once this first step is working and has been tested, the second step implements the guessing game. The game loops, reading a line of user input, converting that C string to an integer, and calling a function (called inlist) that searches the linked list for the integer. With the results of inlist, an appropriate result is printed. The last step in the loop prompts for another user-entered guess.

The character 'q' as the first character entered on a line stops the game and exits the program.

So, this game requires the reading of a user-entered C string. Use the fgets function to help prevent buffer overflow. Use a static declaration of a single buffer (array of characters); the file being read from is stdin; stdin does not need to be opened or closed. An issue you will need to consider is the size of the buffer.

What gets added to the linked list is an integer, but the program reads in a set of characters as a C string. So, the C string must be converted to an integer. Use the atoi function to do the conversion, and don't worry about bad input. What does atoi return if the C string does not represent an integer?

For this portion of the program, add and use these functions:

void playgame(Node * listhead); 
This function receives a pointer to the head of the list of integers. It plays the game, taking care of printing out prompts, reading in the user input, converting the C string to an integer (using atoi), and printing the result of each user's guess. It calls function inlist to search the list for the user's guess.
int inlist(Node *head, int intvalue); 
This function receives a pointer to the head of the list and the integer to search for (intvalue). It iterates through the list, comparing the value in a node to intvalue. If it finds intvalue in the list, the function stops looking at further values and returns the value 1. If the entire list has been searched, and intvalue has not been found, it returns the value 0.
Step 4: A modified game

This third program is a slightly modified version of the game program; call this program game2.c. The only difference between game and this program is the input file format. Instead of reading from a file of integers (binary), the input will be read from a file of ASCII characters (sometimes called a text file).

You created a file of ASCII characters when you redirected the output of generate. That file is what is read by this program. The file format has each integer on its own line of the file.

Start by copying game.c to game2.c. The amount of code that you change in game2.c will be rather small. The user playing the game will see no difference, other than that the command line argument that specifies the input file will be different.

Differences:

Instead of open, use fopen. Read the man page to understand the parameters and return value. This file only needs to be read, so the second parameter will be the C string literal "r".
Instead of close, use fclose.
Instead of read, use fgets. Note that you have already used this function to read the user input in game.c. Again for this program, you will need to make a quality choice for the size of the buffer. Also note that the value that gets added to the list is still an integer, so after reading a C string, use atoi to convert the C string to an integer.
