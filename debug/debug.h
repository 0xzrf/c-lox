#ifndef clox_debug_h
#define clox_debug_h

#include "../compiler/precedence.h"
#include "../opcodes/chunk.h"
#include "../scanner/scanner.h"

void disassemble_chunk(Chunk *chunk, const char *name);
int disassemble_instruction(Chunk *chunk, int offset);
static int simple_instruction(const char *, int);
static int constant_instruction(const char *, Chunk *, int);
char *int_to_token(TokenType);
char *int_to_precedence(Precedence);

#endif
