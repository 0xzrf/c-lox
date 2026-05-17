#ifndef clox_vm_h
#define clox_vm_h

#include "../common/common.h"
#include "../common/memory.h"
#include "../compiler/compiler.h"
#include "../constants/obj.h"
#include "../constants/value.h"
#include "../debug/debug.h"
#include "../opcodes/chunk.h"

#define INIT_MAX_STACK_SIZE 256

#define NEW_STACK_SIZE(old_size) ((old_size) * 1.5)

#define INCR_STACK_SIZE(type, pointer, old_size, new_size)                     \
  ((type *)reallocate(pointer, sizeof(type) * (old_size),                      \
                      sizeof(type) * (new_size)))

typedef struct {
  Chunk *chunk;
  uint8_t *program_counter;
  int stack_size;
  Value *stack;
  Value *stack_top; // points to the top `un-allocated` index of the stack
} VM;

typedef enum {
  COMPILE_TIME_ERROR,
  RUNTIME_ERROR,
  SUCCESSFUL_RUN
} InterpreterResult;

void init_vm();
void free_vm();
void init_stack();
void push(Value);
Value pop();
static Value peek_stack(int);
static void runtime_error(const char *format, ...);
static bool is_falsy(Value);
static void concatenate();
InterpreterResult interpret(const char *);

static InterpreterResult run();

#endif
