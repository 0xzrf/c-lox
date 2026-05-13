#ifndef clox_vm_h
#define clox_vm_h

#include "../opcodes/chunk.h"

#define MAX_STACK_SIZE 256

typedef struct {
    Chunk* chunk;
    uint8_t* program_counter;
    Value stack[MAX_STACK_SIZE];
    Value* stack_top; // points to the top `un-allocated` index of the stack
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

InterpreterResult interpret(Chunk*);

static InterpreterResult run();

#endif
