#ifndef clox_compiler_h
#define clox_compiler_h

#include <stdio.h>
#include "../scanner/scanner.h"
#include "../opcodes/chunk.h"

bool compile(const char*, Chunk*);

#endif
