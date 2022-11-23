#include "kernel/types.h"
#include "user/memory_management.h"
#include "user/user.h"

int main(int argc, char* argv[]) {
  printf("This is the testingo programo\n");

  // create a test array with malloc
  int* int_array = (int*)_malloc(5 * sizeof(int));

  // set all values to 1
  for (int i = 0; i < 5; i++) {
    int_array[i] = i + 1;
  }

  // output array to see if it worked
  for (int i = 0; i < 5; i++) {
    printf("%d ", int_array[i]);
  }
  printf("\n");

  // free it
  _free(int_array);

  exit(0);
}
