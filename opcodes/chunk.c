#include "chunk.h"
#include "memory.h"
#include <stdlib.h>

// initializes a un-initialized chunk struct
void init_chunk(Chunk *chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
}

void write_chunk(Chunk *chunk, uint8_t byte) {
    if (chunk->capacity < chunk->count + 1) {
        // step 1: Increase the capacity
        int old_cap = chunk->capacity;
        int new_cap = GROW_CAPACITY(old_cap);
        // step 2: Allocate -> copy array elem to it -> make `chunk->code` point at it
    }

    chunk->code[chunk->count++] = byte;
}
