#include "compiler.h"

Parser parser;
Chunk* compiling_chunk;

bool compile(const char* source, Chunk* chunk) {
    init_scanner(source);
    init_globals();

    advance_parser();

    consume(TOKEN_EOF, "Expect end of expression.");

    return !parser.had_error;
}

static void emit_byte(uint8_t byte) {
    write_chunk(current_chunk(), byte, parser.prev.line);
}

static void end_compiler() {
    emit_return();
}

static void emit_return() {
    emit_byte(OP_RETURN);
}

static void emit_opcode_with_operands(uint8_t opcode, uint8_t operand) {
    emit_byte(opcode);
    emit_byte(operand);
}

static void init_globals(Chunk* chunk) {
    parser.had_error = false;
    parser.panic_mode = false;

    compiling_chunk = chunk;
}

static void advance_parser() {
    parser.prev = parser.current;

    INFINITE_LOOP {
        parser.current = scan_token();

        if (parser.current.type != TOKEN_ERROR) break;

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

static void error_at_current(const char * message) {
    error_at(&parser.current, message);
}

static void error(const char *message) {
    error_at(&parser.prev, message);
}

static void error_at(Token* token, const char* message) {
  fprintf(stderr, "[line %d] Error", token->line);
  if (parser.panic_mode) return;

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
