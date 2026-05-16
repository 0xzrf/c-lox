#include "logs.h"

#include "../debug/debug.h"
#include <stdio.h>
#include <string.h>

#ifdef DEBUG_COMPILE_LOGS

#define LOG_RULE_WIDTH 64

static void print_rule(char fill) {
  for (int i = 0; i < LOG_RULE_WIDTH; i++) {
    putchar(fill);
  }
  putchar('\n');
}

static void print_label(const char *label) { printf("  %-14s", label); }

void log_title(const char *title) {
  int padding = LOG_RULE_WIDTH - (int)strlen(title) - 4;
  if (padding < 0) {
    padding = 0;
  }

  putchar('\n');
  print_rule('=');
  for (int i = 0; i < padding / 2; i++) {
    putchar(' ');
  }
  printf("  %s  ", title);
  for (int i = 0; i < padding - padding / 2; i++) {
    putchar(' ');
  }
  putchar('\n');
  print_rule('=');
  putchar('\n');
}

void log_subtitle(const char *subtitle) {
  printf("  -- %s ", subtitle);
  int used = 6 + (int)strlen(subtitle);
  int fill = LOG_RULE_WIDTH - used - 2;
  if (fill < 0) {
    fill = 0;
  }
  for (int i = 0; i < fill; i++) {
    putchar('-');
  }
  putchar('\n');
}

void log_comp_vars(Precedence prec, TokenType prev_type,
                   TokenType current_type) {
  print_label("precedence");
  printf("%-20s (%d)\n", int_to_precedence(prec), prec);

  print_label("previous");
  printf("%-20s (%d)\n", int_to_token(prev_type), prev_type);

  print_label("current");
  printf("%-20s (%d)\n", int_to_token(current_type), current_type);

  putchar('\n');
}

#endif
