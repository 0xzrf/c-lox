#ifndef clox_debug_h
#define clox_debug_h

#include "../opcodes/chunk.h"

void disassemble_chunk(Chunk* chunk, const char* name);
int disassemble_instruction(Chunk* chunk, int offset);
static int simple_instruction(const char*, int);
static int constant_instruction(const char*, Chunk*, int);
#endif
