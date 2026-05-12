#ifndef common_memory_h
#define common_memory_h

#include "common.h"

#define MIN_CAP 8

#define GROW_CAPACITY(capacity) \
    ((capacity) < MIN_CAP ? MIN_CAP : (capacity) * 2)

#define GROW_ARRAY(type, pointer, old_cap, new_cap) \
    ((type *)reallocate(pointer, sizeof(type) * old_cap, sizeof(type) * new_cap))

void* reallocate(void* pointer, size_t old_size, size_t new_size);

#endif
