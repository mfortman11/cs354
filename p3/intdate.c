/* 
 * Assignment 3
 * Written by Eric Eichstadt Section 2 & Mike Fortman Section 2
 * CS 354
 * 3/19/2015
 *
 * This program prints out the date and time every 3 seconds until "Control - C" is pressed 5 
 * times. Every time "Control-C" is pressed the program will let the user know how many more 
 * times control C can be pressed until the program terminates. 
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>


/*Global Variables*/
int ControlCCount = 5;

/* Prototypes */
void HandleTheAlarm();
void HandleControlC();


/* The main function of the program. Sets up an alarm, defines how to deal with SIGALRM and SIGINT,
 * Displays introductory text, and creates an infinte loop.
 *
 * Parameters:
 * Argc and *argv[] are never used, but are included just incase this program
 * ever wants to be updated to use command line arguments.
 */
int main(int argc, char *argv[])
{

  /* Setting up the alarm, sets up "SIGALRM" handler*/
  struct sigaction timer;
  timer.sa_handler = HandleTheAlarm;
  timer.sa_flags = 0;
  alarm(3);
  if (sigaction(SIGALRM, &timer , NULL) == -1){
    printf("Error");
    exit(1);
  }

  /* Sets up "SIGINT" handler*/
  struct sigaction controlc;
  controlc.sa_handler = HandleControlC;
  controlc.sa_flags = 0;
  if (sigaction(SIGINT, &controlc , NULL) == -1){
    printf("Error");
    exit(1);
  }

  /* Opening Text */
  printf("Date will be printed every 3 seconds.\n");
  printf("Enter ^C 5 times to end the program:\n");
 
  /* Infinite Loop that does nothing*/
  while(1) {
  }
}


/* This functions is used in response to a user entering in "Control-C". It prints out how
 * many "Control-C"'s until the program exits. If "Control-C" has been pressed 5 times, the 
 * program exits */
void HandleControlC()
{
  /* Update how many times "Control-C" has been pressed, and informs the user how many
   * more until the program terminates */
  if (ControlCCount > 1){
    ControlCCount = ControlCCount - 1;
    printf("\nControl-c caught. %d more before program is ended.\n", ControlCCount);
  }

  /* Checks to see if it is time for the program to exit */
  else{
    printf("\nFinal Control-c caught. Exiting.\n");
    exit(0);
  }
}


/* This function is used in response to an alarm going off. Every time an alarm goes off 
 * it prints the date and time. It then proceeds to reset the alarm. */
void HandleTheAlarm()
{
  time_t currentTime;
  //Getting Current time
  if (time (&currentTime) == -1){
    printf("Error Occured");
  };

  //Printing out current time and resetting
  printf("\ncurrent time is %s", ctime (&currentTime));
  alarm(3);
}
