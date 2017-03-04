/* 
 * Assignment 3 Part 2 division.c 
 * Written by Eric Eichstadt Section 2 & Mike Fortman Section 2
 * CS 354
 * 3/19/2015
 *
 * This program prompts the user for 2 integers to divide and displays the
 * the resulting quotient and remainder. It will continue to do prompt the user
 * for integers to divide until Control+C is clicked or the user tries to
 * divide by zero, in which case the program exits and the number of successful
 * divisions is displayed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

/* Declares prototypes for additional functions*/
void HandleDivByZero();
void HandleControlC();

/* Declares global variable for division counter*/
int divCount = 0;

/* Main method prompts user for integers to divide in an infinite loop. It takes
 * the user input and converts it to an integer then performs a division in an
 * infinite loop. It also handles SIGINT and SIGFPE. It will end the program
 * and print an error message if an error occurs.
 *
 * Parameters:
 *   argc: number of command line arguments (Not used)
 *   *argv[]: an array of points to command line arguments (Not used)
 */
int main(int argc, char *argv[])
{
  /*11 is the max digits required for an integer (10 for largest # + -sign)*/
  char input[11]; 
  /* declares necessary integer variables*/
  int int1 = 0;
  int int2 = 0;
  int quotient = 0;
  int remainder = 0;

  /* Sets up SIGFPE handler (divide by zero operation) */
  struct sigaction divideByZero;
  divideByZero.sa_handler = HandleDivByZero;
  divideByZero.sa_flags = 0;
  if(sigaction(SIGFPE, &divideByZero, NULL) == -1){
    printf("Error\n");
    exit(1);
  }
  
  /* Sets up SIGINT handler (Control+C click) */
  struct sigaction controlc;
  controlc.sa_handler = HandleControlC;
  controlc.sa_flags = 0;
  if (sigaction(SIGINT, &controlc , NULL) == -1){
    printf("Error\n");
    exit(1);
  }

  /* infinite loop */
  while(1){
    printf("Enter first integer: ");
    /* ends program if error occurs */
    if(fgets(input, 11, stdin) == NULL){
      printf("Error\n");
      exit(1);
    }
    int1 = atoi(input); /* converts user input string to integer*/

    printf("Enter second integer: ");
    /* ends program if error occurs */
    if(fgets(input, 11, stdin) == NULL){
      printf("Error\n");
      exit(1);
    }
    int2 = atoi(input); /* converts user input string to integer*/

    /* performs division */
    quotient = int1 / int2;
    remainder = int1 % int2;

    /* if no sigaction is triggered the division counter is incremented*/
    divCount++;    

    /* prints division results */
    printf("%d / %d is %d with a remainder of %d\n", int1, int2, quotient, 
      remainder);
  }
}

/* This functions handles a divide by zero operarion. It will end the program, 
 * print an error message, and the display number of successful divisions.
 */
void HandleDivByZero(){
  printf("A divide by 0 operation was attempted.\n");
  printf("There were %d successful divsion operations.\n", divCount);
  exit(0);
}

/* This functions is used in response to a user entering in "Control-C". 
 * It will end the program and print the number of successful divisions
 */
void HandleControlC()
{
  printf("\nThere were %d successful divsion operations.\n", divCount);;
  exit(0);
}
