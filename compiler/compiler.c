#include "compiler.h"

Parser parser;

bool compile(const char* source, Chunk* chunk) {
    init_scanner(source);

    return true;
}

static void advance_parser() {
    parser.prev = parser.current;

    INFINITE_LOOP {
        parser.current = scan_token();

        if (parser.current.type != TOKEN_ERROR) break;


    }
}

static void error_at_current(const char * message) {
    error_at(&parser.current, message);
}
static void error(const char *message) {
    error_at(&parser.prev, message);
}

static void error_at(Token* token, const char* message) {
  fprintf(stderr, "[line %d] Error", token->line);

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
