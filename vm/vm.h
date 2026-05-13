#ifndef clox_vm_h
#define clox_vm_h

#include "../opcodes/chunk.h"

typedef struct {
    Chunk* chunk;
    uint8_t* program_counter;
} VM;

typedef enum {
    COMPILE_TIME_ERROR,
    RUNTIME_ERROR,
    SUCCESSFUL_RUN
} InterpreterResult;

void init_vm();
void free_vm();

InterpreterResult interpret(Chunk*);

static InterpreterResult run();

#endif
