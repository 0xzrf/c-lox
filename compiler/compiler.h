#ifndef clox_compiler_h
#define clox_compiler_h

#include "../opcodes/chunk.h"
#include "../scanner/scanner.h"
#include "precedence.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  Token prev;
  Token current;
  bool had_error;
  bool panic_mode;
} Parser;

typedef void (*ParseFn)();

typedef struct {
  ParseFn prefix;
  ParseFn infix;
  Precedence precedence;
} ParseRule;

bool compile(const char *, Chunk *);

// error fns
static void error_at(Token *, const char *);
static void error(const char *);
static void error_at_current(const char *);

// global helpers
static void init_globals(Chunk *);
static void consume(TokenType, const char *);
static Chunk *current_chunk(void);
static void advance_parser(void);

// extra helpers
static void emit_byte(uint8_t);
static void end_compiler(void);
static void emit_return(void);
static void emit_opcode_with_operands(uint8_t, uint8_t);
static void emit_constant(Value);

/// bytecode helpers
static void compile_number(void);
static void compile_grouping(void);
static void compile_binary(void);
static void compile_unary(void);
static void compile_literal(void);
static void compile_string(void);
static const ParseRule *get_rule(TokenType);
static uint8_t make_constant(Value);
static void expression(void);
static void parse_precedence(Precedence);

#endif
