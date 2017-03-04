/* Michael Fortman Section 2
 * Eric Eichstadt Section 2
 */
#include <stdio.h>
#include <stdlib.h>

#define arrLength 100000

int arr[100000];

int main(int argc, char *argv[]){
  int i;
  for(i = 0; i < 100000; i++){
    arr[i] = i;
  }
  return 0;
}
