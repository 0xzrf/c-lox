#ifndef clox_logs_h
#define clox_logs_h

#include "../compiler/precedence.h"
#include "../scanner/scanner.h"

char *int_to_precedence(Precedence);
char *int_to_token(TokenType);

#ifdef DEBUG_COMPILE_LOGS

void log_title(const char *title);
void log_subtitle(const char *subtitle);
void log_comp_vars(Precedence prec, TokenType prev_type,
                   TokenType current_type);

#define TITLE(title) log_title(title)
#define SUBTITLE(subtitle) log_subtitle(subtitle)
#define LOG_COMP_VARS(prec, prev_type, current_type)                           \
  log_comp_vars(prec, prev_type, current_type)

#else

#define TITLE(title) ((void)0)
#define SUBTITLE(subtitle) ((void)0)
#define LOG_COMP_VARS(prec, prev_type, current_type) ((void)0)

#endif

#endif
