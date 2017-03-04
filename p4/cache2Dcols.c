/* Michael Fortman Section 2
 * Eric Eichstadt Section 2
 */

#include <stdio.h>
#include <stdlib.h>

#define arrLength 100000

int arr[3000][500];

int main(int argc, char *argv[]){
  int i; /* rows */
  int j; /* cols */
  for(j = 0; j < 500; j++){
    for(i = 0; i < 3000; i++){
      arr[i][j] = i + j;
    }
  }
  return 0;
}
