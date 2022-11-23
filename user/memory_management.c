#include "user/memory_management.h"

#include "kernel/types.h"
#include "user/user.h"

// global for the head of the linked list
memory_block_t* block_head = NULL;

//
// Memory management helper functions
//

// allocate a block of memory using the sbrk system call
memory_block_t* allocate_block(int size, memory_block_t* next) {
  // create the memory block, set it to the start address of sbrk
  memory_block_t* block;
  block = (memory_block_t*)sbrk(0);

  // allocate enough memory for the requested memory size and the associated
  // block metadata
  void* memory_allocation = sbrk(sizeof(memory_block_t) + size);

  // check if has errored, return null if has
  if (memory_allocation == (void*)-1) return NULL;

  // set the memory block flags
  block->is_free = 0;
  block->size = size;
  block->next = (next) ? next : NULL;
  return block;
}

// search though all the blocks in the heap to find one that can fit the
// requested memory size, should return NULL if reached end of list.
memory_block_t* find_block(int size) {
  // start searching from the head of the list
  memory_block_t* current = block_head;

  // loop through to find a block that is free and has enough space
  while (current && !(current->is_free && current->size >= size))
    current = current->next;

  return current;
}

//
// Malloc and Free functions
//

// memory allocation with a requested size
void* _malloc(int size) {
  memory_block_t* block;

  // ensure size is > 0
  if (size <= 0) return NULL;

  if (!block_head) {
    // if is first call
    block = allocate_block(size, NULL);

    // ensure that the creation of the block was successful
    if (!block) return NULL;

    // set this block as the head
    block_head = block;
  } else {
    // else we search though to see if we have an available block
    block = find_block(size);

    // check status of block search
    if (block) {
      // we have found a block that has a minimum size of what we require
      // for now we are going to claim it all but in the future we could
      // split it

      // set the block as being in use
      block->is_free = 0;
    } else {
      // we couldn't find a large enough block so we are going to allocate
      // another memory block
      block = allocate_block(size, block_head);

      // ensure that allocation was successful
      if (!block) return NULL;
    }
  }

  // return pointer to the memory just after the block metadata which
  // is the memory requested
  return ((void*)block) + sizeof(memory_block_t);
}

// free the memory from a malloc
void _free(void* ptr) {
  // ensure that null ptr is handled
  if (!ptr) return;

  // get the pointer to the start of the memory block metadata
  memory_block_t* block = (memory_block_t*)(ptr - sizeof(memory_block_t));

  // set it as free
  block->is_free = 1;

  // Note: in the future we could merge blocks here
}
