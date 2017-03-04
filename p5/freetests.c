#include <assert.h>
#include <stdlib.h>
#include "mem.h"

int main() {
   assert(Mem_Init(4096) == 0);
   void* ptr = Mem_Alloc(23);
   assert(ptr != NULL);
   /* Check that Mem_Free is working correctly */
   assert(Mem_Free(ptr) == 0);
   /* Check that when given NULL Mem_Free returns -1 */
   assert(Mem_Free(NULL) == -1);
   /* Check that when give a bad pointer Mem_Free returns -1 */
   assert(Mem_Free(ptr + 80) == -1);
   exit(0);
}
