Overview

The purpose of this program is gain insight into the asynchronous nature of interrupts, and handling interrupts and traps, while expanding C programming skills. By their very definition, interrupts occur at times not connected to the running program; this makes them asynchronous.

Program Description

This assignment consists of 2 programs, and each will be turned in.

These programs use specific software interrupts, requiring you to set up the capture of the interrupts to be handled, and also provide the handling code.

First Program: A Periodic Alarm

Periodic Alarm: Step 1

Write a C program called intdate.c that is composed of two parts. One part is the main program, which does absolutely nothing in an infinite loop. Before entering the infinite loop, the main program will set up what is to happen when an alarm goes off 3 seconds later. When the alarm goes off, this causes a SIGALRM interrupt to signal the program. This interrupt is to be caught by the program, and handled by the second part of the program, an interrupt handler. This handler function is to print out the current time, in the same format as the Unix date program, re-arm the alarm to go off three seconds later, and then return back to the main program (which continues its infinite loop doing nothing).

Since the program is to keep running forever, main() will contain an infinite loop such as

   while (1) {
   }
As you begin this program, get this alarm working, with this infinite loop (that does nothing useful). For this partially complete program, output will look something like

% intdate
Date will be printed every 3 seconds.
Enter ^C to end the program:
current time is Tue Mar  4 13:15:21 2014
current time is Tue Mar  4 13:15:24 2014
current time is Tue Mar  4 13:15:27 2014
^C
Notice that to stop the program from running, you type in a Control-c. Remember for the next part of this assignment: typing Control-c sends a software interrupt (called SIGINT) to the running program.

Like the set of C programs in Assignment 1, you will use library functions to help you. Just like Assignment 1, it is important to check the return values of these functions, such that your program detects error conditions and acts in response to those errors. Reference the man pages of these functions that you will use:

time() and ctime() are library calls to help your handler obtain and print the time in the correct format.
alarm() activates the SIGALRM interrupt to occur in a specified number of seconds.
sigaction() ( do not use signal() ) sets up what happens when the specific type of interrupt (specified as the first parameter) causes a software interrupt. You are particularly interested in setting the sa_handler field of the structure that sigaction() needs; it specifies the handler function to run upon an interrupt.
Periodic Alarm: Step 2

Once the periodic printing of the time is working, add to the program to do something other than exit the program the first time a Control-c is typed. This extension to program only exits after the user types Control-c 5 times. Set up a SIGINT handler (using sigaction() to set up the call back function). The SIGINT handler either prints how many more times Control-c must be typed before exiting, or it prints that it caught the 5th one and it calls exit().

Output of the program looked like this on Feb 26:

Date will be printed every 3 seconds.
Enter ^C 5 times to end the program:
^C
Control-c caught. 4 more before program is ended.

current time is Thu Feb 26 15:15:51 2015
^C
Control-c caught. 3 more before program is ended.
^C
Control-c caught. 2 more before program is ended.
^C
Control-c caught. 1 more before program is ended.

current time is Thu Feb 26 15:15:54 2015
^C
Final Control-c caught. Exiting.
The alarm interrupt handler will need to re-arm the alarm each time it is called. Since both main() and the alarm handler both need to know/use the number of seconds in order to arm the alarm, make this value a global variable. Interrupt handlers are not invoked by another function within the program, so they cannot receive parameters from another function in the program.

You will also need a global variable to keep track of the number of times a Control-c has been typed. It is only used by the SIGINT handler, but it needs to exist (single instantiation) the entire time that the program runs.

VERY IMPORTANT: Compile the program with a different set of options than used in assignment 1. When grading your programs, we will also use this command. You are leaving off the -O option which invokes the optimizer on your code. If you were to allow the compiler to optimize your code, it might eliminate necessary code.

    % gcc -o intdate intdate.c -Wall -m32
One more note: Even if you have a personal computer with a C compiler, you will not be able to work on your own computer, as the set up and handling of the variety of interrupts is different on different platforms. Work on the galapogos machines to do this assignment.

Second Program: Do Some Division

Write a simple program that loops (forever) to

prompt for and read in one integer value (followed by the newline)
prompt for and read in a second integer value (followed by the newline)
calculate the quotient and remainder of doing the integer division operation: int1 / int2, printing these results, and keeping track of how many division operations were successfully completed.
Place this endless loop into main(). Yes, this is poor style, but do it anyway.

A Control-c will cause this program to stop running.

Use fgets() to read each line of input. Then, use atoi() to translate that C string to an integer.

Users tend to type in bad inputs occasionally. For ease of programming, mostly ignore error checking on the input. If the user enters in a bad integer value, don't check for a bad integer value, and don't worry about it. Just use whatever value atoi() returns. If you still don't know what this value is, look it up in the atoi() man page!

The count of the number of completed divisions needs to be a global variable, as it will be needed by the second program enhancement (described below).

Call the source code for this program division.c.

A sample run of the program might appear as

Enter first integer: 12
Enter second integer: 2
12 / 2 is 6 with a remainder of 0
Enter first integer: 100
Enter second integer: -7
100 / -7 is -14 with a remainder of 2
Enter first integer: 10
Enter second integer: 20
10 / 20 is 0 with a remainder of 10
Enter first integer: ab17
Enter second integer: 3
0 / 3 is 0 with a remainder of 0
Enter first integer: ^C
Once this program is working, enhance it in two ways.

Try your program on a divide by 0 operation. What happens?
The hardware traps when this unrecoverable arithmetic error occurs, and the program crashes, because it did not (catch and) handle the SIGFPE signal.

To make this situation a little bit better, set up a handler that will be called if the program receives the SIGFPE signal. In the signal handler you write, print a message stating that a divide by 0 operation was attempted, print the number of successfully completed division operations, and then exit the program (gracefully, instead of crashing).

You needed to interrupt this program to cause it to stop running. The second enhancement to this program captures the control-c just like the intdate program did, but on the first control-c interrupt, the handler prints the number of successfully completed division operations, and then exits the program (gracefully).
Set up and add a handler for the SIGINT signal. The handler is to print a little message stating the number of completed operations, and then exit the program (gracefully).

Useful functions that you will need to use:

fgets() reads up to a defined maximum number of characters into a buffer, stopping before that maximum is reached if a newline or EOF is encountered.
atoi() converts a C string into the integer represented by that string.
sigaction() ( do not use signal() ) sets up what happens when the specific type of interrupt specified as the first parameter causes a software interrupt. You will be calling sigaction() twice, once to set up the handling of SIGFPE, and another time to set up the handling of SIGINT. Implement 2 independent handlers; do not combine the handlers. Do not place the calls to sigaction() within a loop. These calls will be completed before entering the loop that requests and does division on the two integers.
