#include "debug.h"
#include "../logs/logs.h"
#include <stdint.h>
#include <stdio.h>

void disassemble_chunk(Chunk *chunk, const char *name) {
#if defined(DEBUG_PRINT_CODE) || defined(DEBUG_TRACE_EXECUTION)
  log_disassemble_chunk_header(name);
#else
  printf("=== %s ===\n", name);
#endif

  for (int offset = 0; offset < chunk->count;) {
    offset = disassemble_instruction(chunk, offset);
  }
}

int disassemble_instruction(Chunk *chunk, int offset) {
  int line = get_line(chunk, offset + 1);
  uint8_t instruction = chunk->code[offset];

  switch (instruction) {
  case OP_RETURN:
    return simple_instruction("OP_RETURN", offset, line);
  case OP_NEGATE:
    return simple_instruction("OP_NEGATE", offset, line);
  case OP_ADD:
    return simple_instruction("OP_ADD", offset, line);
  case OP_SUB:
    return simple_instruction("OP_SUB", offset, line);
  case OP_MUL:
    return simple_instruction("OP_MUL", offset, line);
  case OP_DIV:
    return simple_instruction("OP_DIV", offset, line);
  case OP_NOT:
    return simple_instruction("OP_NOT", offset, line);
  case OP_CONSTANT:
    return constant_instruction("OP_CONSTANT", chunk, offset, line);
  default:
#if defined(DEBUG_PRINT_CODE) || defined(DEBUG_TRACE_EXECUTION)
    log_opcode_unknown(offset, line, instruction);
#else
    printf("Unknown opcode %d\n", instruction);
#endif
    return offset + 1;
  }
}

static int simple_instruction(const char *name, int offset, int line) {
#if defined(DEBUG_PRINT_CODE) || defined(DEBUG_TRACE_EXECUTION)
  log_opcode_simple(offset, line, name);
#else
  printf("%04d %4d %s\n", offset, line, name);
#endif
  return offset + 1;
}

static int constant_instruction(const char *name, Chunk *chunk, int offset,
                                int line) {
  uint8_t constant = chunk->code[offset + 1];
  Value value = chunk->constants.value[constant];

#if defined(DEBUG_PRINT_CODE) || defined(DEBUG_TRACE_EXECUTION)
  log_opcode_constant(offset, line, name, constant, value);
#else
  printf("%04d %4d %-16s %4d ", offset, line, name, constant);
  print_value(value, true);
  putchar('\n');
#endif
  return offset + 2;
}

char *int_to_token(TokenType type) {
  switch (type) {
  // Single-character tokens.
  case TOKEN_LEFT_PAREN:
    return "TOKEN_LEFT_PAREN";
  case TOKEN_RIGHT_PAREN:
    return "TOKEN_RIGHT_PAREN";
  case TOKEN_LEFT_BRACE:
    return "TOKEN_LEFT_BRACE";
  case TOKEN_RIGHT_BRACE:
    return "TOKEN_RIGHT_BRACE";
  case TOKEN_COMMA:
    return "TOKEN_COMMA";
  case TOKEN_DOT:
    return "TOKEN_DOT";
  case TOKEN_MINUS:
    return "TOKEN_MINUS";
  case TOKEN_PLUS:
    return "TOKEN_PLUS";
  case TOKEN_SEMICOLON:
    return "TOKEN_SEMICOLON";
  case TOKEN_SLASH:
    return "TOKEN_SLASH";
  case TOKEN_STAR:
    return "TOKEN_STAR";
  // One or two character tokens.
  case TOKEN_BANG:
    return "TOKEN_BANG";
  case TOKEN_BANG_EQUAL:
    return "TOKEN_BANG_EQUAL";
  case TOKEN_EQUAL:
    return "TOKEN_EQUAL";
  case TOKEN_EQUAL_EQUAL:
    return "TOKEN_EQUAL_EQUAL";
  case TOKEN_GREATER:
    return "TOKEN_GREATER";
  case TOKEN_GREATER_EQUAL:
    return "TOKEN_GREATER_EQUAL";
  case TOKEN_LESS:
    return "TOKEN_LESS";
  case TOKEN_LESS_EQUAL:
    return "TOKEN_LESS_EQUAL";
  // Literals.
  case TOKEN_IDENTIFIER:
    return "TOKEN_IDENTIFIER";
  case TOKEN_STRING:
    return "TOKEN_STRING";
  case TOKEN_NUMBER:
    return "TOKEN_NUMBER";
  // Keywords.
  case TOKEN_AND:
    return "TOKEN_AND";
  case TOKEN_CLASS:
    return "TOKEN_CLASS";
  case TOKEN_ELSE:
    return "TOKEN_ELSE";
  case TOKEN_FALSE:
    return "TOKEN_FALSE";
  case TOKEN_FOR:
    return "TOKEN_FOR";
  case TOKEN_FUN:
    return "TOKEN_FUN";
  case TOKEN_IF:
    return "TOKEN_IF";
  case TOKEN_NIL:
    return "TOKEN_NIL";
  case TOKEN_OR:
    return "TOKEN_OR";
  case TOKEN_PRINT:
    return "TOKEN_PRINT";
  case TOKEN_RETURN:
    return "TOKEN_RETURN";
  case TOKEN_SUPER:
    return "TOKEN_SUPER";
  case TOKEN_THIS:
    return "TOKEN_THIS";
  case TOKEN_TRUE:
    return "TOKEN_TRUE";
  case TOKEN_VAR:
    return "TOKEN_VAR";
  case TOKEN_WHILE:
    return "TOKEN_WHILE";
  case TOKEN_ERROR:
    return "TOKEN_ERROR";
  case TOKEN_EOF:
    return "TOKEN_EOF";
  default:
    return "UNKNOWN_TOKEN";
  }
}

char *int_to_precedence(Precedence precedence) {
  switch (precedence) {
  case PREC_NONE:
    return "PREC_NONE";
  case PREC_ASSIGNMENT:
    return "PREC_ASSIGNMENT";
  case PREC_OR:
    return "PREC_OR";
  case PREC_AND:
    return "PREC_AND";
  case PREC_EQUALITY:
    return "PREC_EQUALITY";
  case PREC_COMPARISON:
    return "PREC_COMPARISON";
  case PREC_TERM:
    return "PREC_TERM";
  case PREC_FACTOR:
    return "PREC_FACTOR";
  case PREC_UNARY:
    return "PREC_UNARY";
  case PREC_CALL:
    return "PREC_CALL";
  case PREC_PRIMARY:
    return "PREC_PRIMARY";
  default:
    return "UNKNOWN_PRECEDENCE";
  }
}
