#include <stdlib.h>
#include <stdio.h>

#include "chunk.h"
#include "../common/memory.h"


// initializes a un-initialized chunk struct
void init_chunk(Chunk *chunk) {
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    chunk->line_count = 0;
    init_value_array(&chunk->constants);
}

void write_chunk(Chunk *chunk, uint8_t byte, int line) {
    if (line <= 0) {
        printf("Expected line number to be > 0");
        exit(1);
    }

    if (chunk->capacity < chunk->count + 1) {
        // step 1: Increase the capacity
        int old_cap = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(old_cap);
        int old_line_counts = chunk->line_count;
        chunk->line_count = GROW_CAPACITY(old_line_counts);
        // step 2: Allocate -> copy array elem to it -> make `chunk->code` point at it
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, old_cap, chunk->capacity);
        chunk->lines = GROW_ARRAY(char, chunk->lines, old_line_counts, chunk->line_count);
    }

    if (line > chunk->line_count) {
        chunk->line_count = line;
    }

    chunk->lines[line]++;
    chunk->code[chunk->count++] = byte;
}

void free_chunk(Chunk *chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(char, chunk->lines, chunk->line_count);
    free_value_array(&chunk->constants);
    init_chunk(chunk);
}

int add_constant(Chunk * chunk, Value value) {
    write_value_array(&chunk->constants, value);
    return chunk->constants.count - 1;
}

char get_line(Chunk* chunk, int instruction_ix) {
    char prev_line;
    int i;

    for (prev_line = 1, i = 1; i <= chunk->line_count; i++) {
        if (instruction_ix >= prev_line && instruction_ix <= prev_line + chunk->lines[i]) {
            return i;
        }
        prev_line += chunk->lines[i];
    }

    return -1;
}
