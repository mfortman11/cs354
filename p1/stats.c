/* Assignment1 Stats Program
 * by Eric Eichstadt, section 2 and Mike Fortman section 2
 * CS 354
 * 2/10/2015
 *
 * This program takes in a file composing of binary numbers
 * as a command line argument.The program reads the numbers, 
 * and puts the numbers into an array. The program then prints out
 * the number of integers in the file, as well as the average of 
 * all the integers.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>

/* Main runs the program as described above. It takes in a file name
 * as a command line argument. It will print the number of integers
 * in the file, the average of the integers, and any errors that occur 
 * while reading it.
 *
 * Parameters:
 *  argc: Represents the number of command line parameters
 *  argv[0]: Represents the name of a file comprising of 32-bit
 *  two's complement integers 
 */

int main(int argc, char *argv[])
{

  /* Variables */
  char *infile;
  int fd;
  int *arrayOfInts;
  int i;
  int sum;
  int numberOfInts;
  int average; 
  infile = argv[1];
  struct stat st; 
  
  /* Checking for correct arguments */
  if (argc != 2) {
    printf("Error: Incorrect Arguments\n");
    exit(1);
  }

  /* Opening file and checking for errors*/
  fd = open(infile, O_RDONLY);
  if(fd == 0) {
    printf("Unable to open file\n");
    exit(1);
  }

  /*Getting file size, and allocating an array */
  if(fstat(fd, &st) != 0) {
    printf("error getting file size\n");
    exit(1);
  };
  arrayOfInts = malloc(st.st_size); /* Allocate an array of correct file size */
  numberOfInts = (st.st_size/sizeof(int)); /* calculation for number of ints */

  /*Reading the file, and placing into array. Prints error if unable to read size */
  for(i = 0; i < numberOfInts; i++){
    if(read(fd, &arrayOfInts[i], sizeof(int)) < 0) {
      printf("error reading file");
      exit(1);
    }
  }
 
  /* Closing file, prints an error if there are problems */
  if(close(fd) == -1){
    printf("error closing file");
    exit(1);
  }; 
  
  /* Computing sum */
  sum = 0;
  for(i = 0; i < numberOfInts; i++){
    sum += arrayOfInts[i];
  }

  /* Computing average */
  average = 0;
  average = sum/numberOfInts;

  /*printing results*/
  printf("Number of numbers averaged: %d\n", numberOfInts);
  printf("Average: %d\n", average);
  exit(0);
}
