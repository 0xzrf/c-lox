#ifndef clox_compiler_h
#define clox_compiler_h

#include <stdio.h>
#include "../scanner/scanner.h"
#include "../opcodes/chunk.h"

typedef struct {
    Token prev;
    Token current;
    bool had_error;
    bool panic_mode;
} Parser;

bool compile(const char*, Chunk*);
static void advance_parser(void);
static void error_at(Token*, const char*);
static void error(const char*);
static void error_at_current(const char*);
static void init_parser(void);
static void consume(TokenType, const char*);


#endif
