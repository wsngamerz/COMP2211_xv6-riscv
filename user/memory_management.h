#include <stddef.h>

// Types
struct memory_block {
  int is_free;
  int size;
  struct memory_block* next;
};
typedef struct memory_block memory_block_t;

// make this variable global so we can access it in our test script
// NOTE: this is for debug purposes, remember to removed before submission
extern memory_block_t* block_head;

// helper functions
memory_block_t* allocate_block(int size, memory_block_t* next);
memory_block_t* find_block(int size);
memory_block_t* split_block(int size, memory_block_t* parent);

// malloc and free functions
void* _malloc(int size);
void _free(void* ptr);
