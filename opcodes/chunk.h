#ifndef clox_chunk_h
#define clox_chunk_h

#include "../common.h"

// The list of all the bytecodes supported by the VM
typedef enum {
    OP_RETURN,
} OpCode;

typedef struct {
    int count; // the count of elements in use by `code`
    int capacity; // the capacity of the dynamic array `code`
    uint8_t* code; // the actual (dynamic)array of bytecodes
} Chunk;

void init_chunk(Chunk* chunk);
void write_chunk(Chunk* chunk, uint8_t byte);

#endif
