/* 
 * Assignment 1 Part 3 game.c 
 * Written by Eric Eichstadt Section 2 & Mike Fortman Section 2
 * CS 354
 * 2/9/2015
 *
 * This program reads in a binary file from a command line arguement
 * and adds the integers in the file to a linked list.  It then prompts
 * the user to guess integers to see if they are in the list and lets
 * the user know if there guess is in the list. To exit the game the user
 * enters 'q'.
 */


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <unistd.h>


/*Defines a Node*/
typedef struct node{
  int num;
  struct node *n;
} Node;


/* Declares prototypes for additional functions*/
Node * createlist(int fd);
Node * listadd(Node *head, int intforlist);
void playgame(Node * listhead);
int inlist(Node *head, int intvalue);


/* main uses 1 command line arguement to find and read a binary file
 * and add its content to a linkedlist using the createlist function.
 * It also calls playgame to allow the user to guess the files content.
 * It will print an error message and end the program if something goes wrong.
 *
 * Parameters:
 *   argc: number of command line arguments
 *   *argv[]: an array of points to command line arguments
 *   argv[0]: name of a binary file
 */
int main(int argc, char *argv[])
{
  char *infile; /*pointer to file name char array*/
  int fd; /*file descriptor*/
  infile = argv[1];
  
  /* Checking for correct arguments */
  if (argc != 2) {
    printf("Error: Incorrect Arguments\n");
    exit(1);
  }

  /* Opening file */
  fd = open(infile, O_RDONLY);
  if(fd == 0) {
    printf("Unable to open file\n");
    exit(1);
  }

  /* Creates linked list by calling createlist*/
  Node * listHead = createlist(fd);
  if(listHead == NULL){
    printf("Error reading file or adding to list\n");
    exit(1);
  }
	
  /* Closing file */
  if(close(fd) == -1){
    printf("error closing file");
  }; 
	
  /*Starts the game by calling playgame*/
  playgame(listHead);

  /*ends program when finished*/
  exit(0);
}


/* createlist takes in a file descriptor and creates a NULL Node pointer to
 * then reads through the file associated w/ the file descriptor. Calls listadd
 * to create a new node for integer to be added to the linkedlist.  It then
 * returns a pointer to the 'head' Node. (this will be NULL if file is empty)
 * 
 * Parameters:
 *   fd: an integer representing the file descriptor
 */
Node *createlist(int fd){
  Node *head = NULL; /*intializes a pointer to a head Node as NULL*/
  int num;
  while(read(fd, &num, sizeof(int))>0){
    head = listadd(head, num);  /*head will now point to newest node in list*/
  }
  return head; /*returns the 'head' pointer*/
}


/* listadd creates a new node containing the passed integer and points to the
 * address of the current 'head' node which is passed in. Returns a pointer to
 * the newly created Node.
 *
 * Parameters:
 *   *head: pointer to the current 'head' node
 *   intforlist: integer for the new node to store
 */
Node * listadd(Node *head, int intforlist){
  /* creates new pointer to a Node and allocates the correct amount of space*/
  Node * new = malloc(sizeof(Node));
  new->num = intforlist; /*new node now stores the passed int*/
  new->n = head; /*new node now points to the current 'head' node*/
  return new; /*returns the pointer to the new node*/
}


/* playgame prints instructions for the game and will ask user for new guesses
 * and let them know if it exists in the binary file until the user enters 'q'.
 *
 * Parameters:
 *   *listhead: a pointer to the node at the head of the linkedlist
 */
void playgame(Node * listhead){
  /*11 is the max digits required for an integer (10 for largest # + -sign)*/
  char input[11]; 
  int number;

  /*game instructions*/
  printf("This game has you guess which integers are in the list.\n");
  printf("Enter an integer (followed by the newline)\n");
  printf("or q (followed by the newline) to quit.\n");

  /*continues to ask for user guesses until they enter 'q'.*/
  while(input[0] != 'q'){
    printf("Integer guess: ");
    fgets(input, 11, stdin);
    /*ends program if 'q' is entered*/
    if(input[0] == 'q'){
      exit(0);
    }
    number = atoi(input); /*converts char[] to integer (0 if not an int)*/
    
    /*checks linkedlist for the int guessed by the user*/
    if(inlist(listhead, number) == 1){
      printf("%i", number);
      printf(" is in the list.\n"); /*prints result if found*/
    }
    else{
      printf("%i", number);
      printf(" is not in the list.\n"); /*prints result if not found*/
    }
  } 
}


/* inlist searches through the linkedlist to see if the passed integer is in
 * the list. It will return 1 if the int is found or 0 if it is not.
 *
 * Parameters:
 *   *head: pointer to the node at the 'head' of the linkedlist
 *   intvalue: the integer value to search for in the linkedlist
 */
int inlist(Node *head, int intvalue){
  /*searches through the linkedlist as long as the head is not NULL*/
  while(head){
    if(head->num == intvalue){
      return 1; /*returns 1 if found*/
    }
    head = head->n; /*advance to the next node in the list*/
  }
  return 0; /*return 0 if not found after traversing the whole list*/
}


