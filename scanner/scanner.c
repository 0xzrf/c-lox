#include <stdio.h>
#include <string.h>

#include "../common/common.h"
#include "scanner.h"

Scanner scanner;

void init_scanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

Token scan_token(void) {
    // we can confidently set start to current, since we guarentee that we will
    // consume the entire valid lexeme from the source code
    scanner.start = scanner.current;

    if (is_at_end())
        return make_token(TOKEN_EOF);

    return error_token("Unexpected character.");
}

static Token make_token(TokenType type) {
    Token token;

    token.line = scanner.line;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.type = type;

    return token;
}

static bool is_at_end() {
    return *scanner.current == '\0';
}

static Token error_token(const char* message) {
  Token token;
  token.type = TOKEN_ERROR;
  token.start = message;
  token.length = (int)strlen(message);
  token.line = scanner.line;
  return token;
}
