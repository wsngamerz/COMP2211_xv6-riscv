#include "kernel/types.h"
#include "user/memory_management.h"
#include "user/user.h"

void output_all_blocks() {
  printf("[MM] =========== Output Blocks ===========\n");
  printf("[MM] | Location\t | Size\t | Status\t |\n");
  printf("[MM] |-----------|-------|---------------|\n");

  // set the current block as the head of the blocks
  memory_block_t* current = block_head;

  // loop through every block and output some details
  while (current) {
    printf("[MM] | 0x%x\t | %db\t | %s\t |\n",
      current,
      current->size,
      (current->is_free == 1) ? "Free\t" : "Taken");
    current = current->next;
  }

  printf("[MM] =====================================\n\n");
}

void* malloc_plus(int size) {
  void* pointer = _malloc(size);
  output_all_blocks();
  return pointer;
}

void free_plus(void* ptr) {
  _free(ptr);
  output_all_blocks();
}

int main(int argc, char* argv[]) {
  printf("This is the testingo programo\n");

  // create a test array with malloc
  int* int_array = (int*)malloc_plus(5 * sizeof(int));
  int* int_array_2 = (int*)malloc_plus(10 * sizeof(int));

  // set all values to incrementing numbers
  for (int i = 0; i < 5; i++) {
    int_array[i] = i + 1;
  }

  for (int i = 0; i < 10; i++) {
    int_array_2[i] = i + 1;
  }

  // output array to see if it worked
  for (int i = 0; i < 5; i++) {
    printf("%d ", int_array[i]);
  }
  printf("\n");

  // free it
  free_plus(int_array);

  // allocate a really small amount of space
  int* number = malloc_plus(sizeof(int));
  number[0] = 10;
  free_plus(number);

  // alocate another int array of length 3
  int* int_array_3 = (int*)malloc_plus(3 * sizeof(int));

  for (int i = 0; i < 3; i++) {
    int_array_3[i] = i + 1;
  }

  free_plus(int_array_2);

  // create a multi dimension array
  int rows = 3;
  int cols = 3;
  int* md_array[rows];

  for (int i = 0; i < rows; i++)
    md_array[i] = (int*)malloc_plus(cols * sizeof(int));

  // populate the array
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      md_array[i][j] = i * j;
    }
  }

  // free previously used array
  free_plus(int_array_3);

  // free the multi-dimensional array
  for (int i = 0; i < rows; i++) {
    free_plus(md_array[i]);
  }

  printf("block head: %x", block_head);

  exit(0);
}
