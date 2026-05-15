#include "compiler.h"
#include "errors.h"

Parser parser;

static void init_parser() {
    parser.had_error = false;
    parser.panic_mode = false;
}

bool compile(const char* source, Chunk* chunk) {
    init_scanner(source);
    init_parser();

    advance_parser();

    consume(TOKEN_EOF, "Expect end of expression.");

    return !parser.had_error;
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
