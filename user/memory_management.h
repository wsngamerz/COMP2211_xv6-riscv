#include <stddef.h>

// Types
struct memory_block {
  int is_free;
  int size;
  struct memory_block* next;
};
typedef struct memory_block memory_block_t;

// helper functions
memory_block_t* allocate_block(int size, memory_block_t* next);
memory_block_t* find_block(int size);
memory_block_t* split_block(int size, memory_block_t* parent);

// malloc and free functions
void* _malloc(int size);
void _free(void* ptr);
