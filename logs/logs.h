#ifndef clox_logs_h
#define clox_logs_h

#include "../compiler/precedence.h"
#include "../constants/value.h"
#include "../scanner/scanner.h"
#include <stdint.h>

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

#if defined(DEBUG_PRINT_CODE) || defined(DEBUG_TRACE_EXECUTION)

void log_disassemble_chunk_header(const char *name);
void log_opcode_simple(int offset, int line, const char *name);
void log_opcode_constant(int offset, int line, const char *name,
                         uint8_t constant_index, Value constant_value);
void log_opcode_unknown(int offset, int line, uint8_t opcode);

#endif

#ifdef DEBUG_TRACE_EXECUTION

void log_vm_step_divider(void);
void log_vm_stack(Value *stack_bottom, Value *stack_top);

#endif

#endif
