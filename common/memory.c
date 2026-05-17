#include "memory.h"
#include <stdlib.h>

void *reallocate(void *pointer, size_t old_size, size_t new_size) {
  if (new_size == 0) {
    free(pointer);
    return NULL;
  }

  void *result = realloc(pointer, new_size);

  // in case of failure, exit the program
  if (result == NULL) {
    exit(1);
  }

  return result;
}
