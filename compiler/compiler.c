#include "compiler.h"
#include <stdlib.h>

#ifdef DEBUG_PRINT_CODE
#include "../debug/debug.h"
#endif

Parser parser;
Chunk *compiling_chunk;
const ParseRule rules[] = {
    [TOKEN_LEFT_PAREN] = {compile_grouping, NULL, PREC_NONE},
    [TOKEN_RIGHT_PAREN] = {NULL, NULL, PREC_NONE},
    [TOKEN_LEFT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_RIGHT_BRACE] = {NULL, NULL, PREC_NONE},
    [TOKEN_COMMA] = {NULL, NULL, PREC_NONE},
    [TOKEN_DOT] = {NULL, NULL, PREC_NONE},
    [TOKEN_MINUS] = {compile_unary, compile_binary, PREC_TERM},
    [TOKEN_PLUS] = {NULL, compile_binary, PREC_TERM},
    [TOKEN_SEMICOLON] = {NULL, NULL, PREC_NONE},
    [TOKEN_SLASH] = {NULL, compile_binary, PREC_FACTOR},
    [TOKEN_STAR] = {NULL, compile_binary, PREC_FACTOR},
    [TOKEN_BANG] = {compile_unary, NULL, PREC_NONE},
    [TOKEN_BANG_EQUAL] = {NULL, NULL, PREC_NONE},
    [TOKEN_EQUAL] = {NULL, NULL, PREC_NONE},
    [TOKEN_EQUAL_EQUAL] = {NULL, NULL, PREC_NONE},
    [TOKEN_GREATER] = {NULL, NULL, PREC_NONE},
    [TOKEN_GREATER_EQUAL] = {NULL, NULL, PREC_NONE},
    [TOKEN_LESS] = {NULL, NULL, PREC_NONE},
    [TOKEN_LESS_EQUAL] = {NULL, NULL, PREC_NONE},
    [TOKEN_IDENTIFIER] = {NULL, NULL, PREC_NONE},
    [TOKEN_STRING] = {NULL, NULL, PREC_NONE},
    [TOKEN_NUMBER] = {compile_number, NULL, PREC_NONE},
    [TOKEN_AND] = {NULL, NULL, PREC_NONE},
    [TOKEN_CLASS] = {NULL, NULL, PREC_NONE},
    [TOKEN_ELSE] = {NULL, NULL, PREC_NONE},
    [TOKEN_FALSE] = {compile_literal, NULL, PREC_NONE},
    [TOKEN_FOR] = {NULL, NULL, PREC_NONE},
    [TOKEN_FUN] = {NULL, NULL, PREC_NONE},
    [TOKEN_IF] = {NULL, NULL, PREC_NONE},
    [TOKEN_NIL] = {compile_literal, NULL, PREC_NONE},
    [TOKEN_OR] = {NULL, NULL, PREC_NONE},
    [TOKEN_PRINT] = {NULL, NULL, PREC_NONE},
    [TOKEN_RETURN] = {NULL, NULL, PREC_NONE},
    [TOKEN_SUPER] = {NULL, NULL, PREC_NONE},
    [TOKEN_THIS] = {NULL, NULL, PREC_NONE},
    [TOKEN_TRUE] = {compile_literal, NULL, PREC_NONE},
    [TOKEN_VAR] = {NULL, NULL, PREC_NONE},
    [TOKEN_WHILE] = {NULL, NULL, PREC_NONE},
    [TOKEN_ERROR] = {NULL, NULL, PREC_NONE},
    [TOKEN_EOF] = {NULL, NULL, PREC_NONE},
};

bool compile(const char *source, Chunk *chunk) {
  TITLE("compile start");
  init_scanner(source);
  init_globals(chunk);

  advance_parser();
  expression();
  emit_return();

  consume(TOKEN_EOF, "Expect end of expression.");

  TITLE("compile end");
  return !parser.had_error;
}

static void compile_number() {
  double value = strtod(parser.prev.start, NULL);
  emit_constant(NUMBER_VAL(value));
}

static void compile_grouping() {
  expression();
  consume(TOKEN_RIGHT_PAREN, "Expected ) after expression");
}

static void compile_unary() {
  TokenType operator_type = parser.prev.type;

  parse_precedence(PREC_UNARY);

  // Compile the operand.
  expression();

  switch (operator_type) {
  case TOKEN_BANG:
    emit_byte(OP_NOT);
    break;

  case TOKEN_MINUS:
    emit_byte(OP_NEGATE);
    break;
  default:
    return;
  }
}

static void compile_literal() {
  switch (parser.prev.type) {
  case TOKEN_FALSE:
    emit_byte(OP_FALSE);
    break;
  case TOKEN_TRUE:
    emit_byte(OP_TRUE);
    break;
  case TOKEN_NIL:
    emit_byte(OP_NIL);
    break;
  default:
    return; // unreachable
  }
}

static void compile_binary() {
  TokenType operatorType = parser.prev.type;
  ParseRule *rule = get_rule(operatorType);
  parse_precedence((Precedence)(rule->precedence + 1));

  switch (operatorType) {
  case TOKEN_PLUS:
    emit_byte(OP_ADD);
    break;
  case TOKEN_MINUS:
    emit_byte(OP_SUB);
    break;
  case TOKEN_STAR:
    emit_byte(OP_MUL);
    break;
  case TOKEN_SLASH:
    emit_byte(OP_DIV);
    break;
  default:
    return; // Unreachable.
  }
}

const static ParseRule *get_rule(TokenType type) { return &rules[type]; }

static void parse_precedence(Precedence precedence) {
  advance_parser();

  SUBTITLE("parse_precedence");
  LOG_COMP_VARS(precedence, parser.prev.type, parser.current.type);

  ParseFn prefix_rule = get_rule(parser.prev.type)->prefix;
  if (prefix_rule == NULL) {
    error("Expect expression.");
    return;
  }

  prefix_rule();

  while (precedence <= get_rule(parser.current.type)->precedence) {
    printf("Precedence fn: %s\nPrecedence current: %s\n",
           int_to_precedence(precedence),
           int_to_precedence(get_rule(parser.current.type)->precedence));
    advance_parser();
    ParseFn infix_rule = get_rule(parser.prev.type)->infix;
    infix_rule();
  }
}

static void expression() { parse_precedence(PREC_ASSIGNMENT); }

static uint8_t make_constant(Value value) {
  int constant = add_constant(current_chunk(), value);
  if (constant > UINT8_MAX) {
    error("Too many constants");
    return 0;
  }

  return (uint8_t)constant;
}

static void emit_byte(uint8_t byte) {
  write_chunk(current_chunk(), byte, parser.prev.line);
}

static void emit_constant(Value value) {
  emit_opcode_with_operands(OP_CONSTANT, make_constant(value));
}

static void end_compiler() {
  emit_return();
#ifdef DEBUG_PRINT_CODE
  if (!parser.had_error) {
    disassemble_chunk(current_chunk(), "code");
  }
#endif
}

static void emit_return() { emit_byte(OP_RETURN); }

static void emit_opcode_with_operands(uint8_t opcode, uint8_t operand) {
  emit_byte(opcode);
  emit_byte(operand);
}

static Chunk *current_chunk() { return compiling_chunk; }

static void init_globals(Chunk *chunk) {
  parser.had_error = false;
  parser.panic_mode = false;

  compiling_chunk = chunk;
}

static void advance_parser() {
  parser.prev = parser.current;

  INFINITE_LOOP {
    parser.current = scan_token();

    if (parser.current.type != TOKEN_ERROR)
      break;

    error_at_current(parser.current.start);
  }
}

static void consume(TokenType ty, const char *message) {
  if (parser.current.type == ty) {
    advance_parser();
    return;
  }

  error_at_current(message);
}

static void error_at_current(const char *message) {
  error_at(&parser.current, message);
}

static void error(const char *message) { error_at(&parser.prev, message); }

static void error_at(Token *token, const char *message) {
  fprintf(stderr, "[line %d] Error", token->line);
  if (parser.panic_mode)
    return;

  if (token->type == TOKEN_EOF) {
    fprintf(stderr, " at end");
  } else if (token->type == TOKEN_ERROR) {
    // Nothing.
  } else {
    fprintf(stderr, " at '%.*s'", token->length, token->start);
  }

  fprintf(stderr, ": %s\n", message);
  parser.had_error = true;
}
