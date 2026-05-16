#include "logs.h"

#include "../constants/value.h"
#include "../debug/debug.h"
#include <stdio.h>
#include <string.h>

#define LOG_RULE_WIDTH 64

static void print_rule(char fill) {
  for (int i = 0; i < LOG_RULE_WIDTH; i++) {
    putchar(fill);
  }
  putchar('\n');
}

static void print_label(const char *label) { printf("  %-14s", label); }

static void print_centered_title(const char *title) {
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

static void print_section_rule(const char *subtitle) {
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

#ifdef DEBUG_COMPILE_LOGS

void log_title(const char *title) { print_centered_title(title); }

void log_subtitle(const char *subtitle) { print_section_rule(subtitle); }

void log_comp_vars(Precedence prec, TokenType prev_type, TokenType current_type) {
  print_label("precedence");
  printf("%-20s (%d)\n", int_to_precedence(prec), prec);

  print_label("previous");
  printf("%-20s (%d)\n", int_to_token(prev_type), prev_type);

  print_label("current");
  printf("%-20s (%d)\n", int_to_token(current_type), current_type);

  putchar('\n');
}

#endif

#if defined(DEBUG_PRINT_CODE) || defined(DEBUG_TRACE_EXECUTION)

void log_disassemble_chunk_header(const char *name) {
  print_centered_title(name);
}

void log_opcode_simple(int offset, int line, const char *name) {
  printf("  %04d | %4d | %s\n", offset, line, name);
}

void log_opcode_constant(int offset, int line, const char *name,
                         uint8_t constant_index, double constant_value) {
  printf("  %04d | %4d | %-16s %3d ", offset, line, name, constant_index);
  print_value(constant_value, true);
  putchar('\n');
}

void log_opcode_unknown(int offset, int line, uint8_t opcode) {
  printf("  %04d | %4d | unknown opcode %u\n", offset, line, opcode);
}

#endif

#ifdef DEBUG_TRACE_EXECUTION

void log_vm_step_divider(void) { print_section_rule("vm step"); }

void log_vm_stack(double *stack_bottom, double *stack_top) {
  print_label("stack");
  if (stack_bottom >= stack_top) {
    printf("(empty)\n");
    return;
  }

  for (double *slot = stack_bottom; slot < stack_top; slot++) {
    putchar('[');
    print_value(*slot, false);
    putchar(']');
  }
  putchar('\n');
}

#endif
