#ifndef clox_chunk_h
#define clox_chunk_h

#include "../common/common.h"
#include "../constants/value.h"
// The list of all the bytecodes supported by the VM
typedef enum {
    OP_CONSTANT,
    OP_RETURN,
} OpCode;

typedef struct {
    int count; // the count of elements in use by `code`
    int capacity; // the capacity of the dynamic array `code`
    uint8_t* code; // the actual (dynamic)array of bytecodes
    char* lines; // this will act as a key pair. So for line number 1, it will determine the instructions associated with that line
    int line_count;
    ValueArray constants; // constants that're referred to in the bytecodes(like `1 + 2` can be converted to immediate `3`)
} Chunk;

void init_chunk(Chunk*);
void write_chunk(Chunk*,uint8_t, int);
void free_chunk(Chunk*);
int add_constant(Chunk*,Value);
char get_line(Chunk*, int);

#endif
