#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vm.h"
#include "vm_helpers.h"

VM vm;

InterpreterResult interpret(const char *source) {
  Chunk chunk;

  init_chunk(&chunk);

  if (!compile(source, &chunk)) {
    free_chunk(&chunk);
    return COMPILE_TIME_ERROR;
  }

  vm.chunk = &chunk;
  vm.program_counter = vm.chunk->code;

  InterpreterResult result = run();

  free_chunk(&chunk);
  return result;
}

static InterpreterResult run() {
#define READ_BYTE() (*vm.program_counter++)
#define READ_CONSTANT() (vm.chunk->constants.value[READ_BYTE()])
#define BINARY_OP(value_type, op)                                              \
  do {                                                                         \
    if (!IS_NUM(peek_stack(0)) || !IS_NUM(peek_stack(1))) {                    \
      runtime_error("operands must be of type number.");                       \
      return RUNTIME_ERROR;                                                    \
    }                                                                          \
    double b = AS_NUMBER(pop());                                               \
    double a = AS_NUMBER(pop());                                               \
    push(value_type(a op b));                                                  \
  } while (false)

  INFINITE_LOOP {
#ifdef DEBUG_TRACE_EXECUTION
    log_vm_step_divider();
    log_vm_stack(vm.stack, vm.stack_top);
    disassemble_instruction(vm.chunk,
                            (int)(vm.program_counter - vm.chunk->code));
    putchar('\n');
#endif

    uint8_t instruction;
    Value constant;

    switch (instruction = READ_BYTE()) {
    case OP_CONSTANT:
      constant = READ_CONSTANT();
      push(constant);
      break;

    case OP_ADD:
      BINARY_OP(NUMBER_VAL, +);
      break;
    case OP_SUB:
      BINARY_OP(NUMBER_VAL, -);
      break;
    case OP_MUL:
      BINARY_OP(NUMBER_VAL, *);
      break;
    case OP_DIV:
      BINARY_OP(NUMBER_VAL, /);
      break;
    case OP_NIL:
      push(NIL_VAL);
      break;
    case OP_FALSE:
      push(BOOL_VAL(false));
      break;
    case OP_TRUE:
      push(BOOL_VAL(true));
      break;

    case OP_EQUAL:
      Value b = pop();
      Value a = pop();
      push(BOOL_VAL(values_equal(a, b)));
      break;
    case OP_GREATER:
      BINARY_OP(BOOL_VAL, >);
      break;
    case OP_LESS:
      BINARY_OP(BOOL_VAL, <);
      break;

    case OP_NOT:
      push(BOOL_VAL(is_falsy(pop())));
      break;
    case OP_NEGATE:
      if (!IS_NUM(peek_stack(0))) {
        runtime_error("Operand must be a number.");
        return RUNTIME_ERROR;
      }
      _negate_last_stack_var(&vm);
      break;
    case OP_RETURN:
      print_value(pop(), true);
      return SUCCESSFUL_RUN;
    }
  }

#undef READ_CONSTANT
#undef READ_BYTE
#undef BINARY_OP
}

void init_vm() { init_stack(); }

// intialize stack_top to be = stack, that means the stack is empty
void init_stack() {
  vm.stack_size = INIT_MAX_STACK_SIZE;

  Value *new_stack = realloc(vm.stack, vm.stack_size * sizeof(*vm.stack));
  if (new_stack == NULL) {
    // handle allocation failure
    abort();
  }

  vm.stack = new_stack;
  vm.stack_top = vm.stack;
}

void push(Value value) {
  // Some big programs might end up taking the entire stack
  // so it's important to make it dynamic and increase it's size
  if (vm.stack - vm.stack_top + 1 > vm.stack_size) {
    int old_stack_size = vm.stack_size;
    vm.stack_size = NEW_STACK_SIZE(old_stack_size);
    vm.stack = INCR_STACK_SIZE(Value, vm.stack, old_stack_size, vm.stack_size);
  }

  *vm.stack_top++ = value;
}

static Value peek_stack(int distance) { return *(vm.stack_top - 1 - distance); }

Value pop() {
  return *--vm.stack_top; // decrement vm.stack_top first, and then dereference
                          // it
}

static bool is_falsy(Value value) {
  return IS_NIL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

static void runtime_error(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
  fputs("\n", stderr);

  size_t instruction = vm.program_counter - vm.chunk->code - 1;
  int line = vm.chunk->lines[instruction];
  fprintf(stderr, "[line %d] in script\n", line);
  // resetStack();
}

void free_vm() {}