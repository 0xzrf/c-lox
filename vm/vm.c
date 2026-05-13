#include <stdio.h>

#include "vm.h"
#include "../common/common.h"
#include "../debug/debug.h"

VM vm;

void init_vm() {
    init_stack();
}

// intialize stack_top to be = stack, that means the stack is empty
void init_stack() {
    vm.stack_top = vm.stack;
}

void push(Value value) {
    *vm.stack_top++ = value;
}

Value pop() {
    return *--vm.stack_top; // decrement vm.stack_top first, and then dereference it
}

void free_vm() {}

InterpreterResult interpret(Chunk* chunk) {
    vm.chunk = chunk;
    vm.program_counter = chunk->code;
    return run();
}

static InterpreterResult run() {
    #define READ_BYTE() (*vm.program_counter++)
    #define READ_CONSTANT() (vm.chunk->constants.value[READ_BYTE()])

    while (true) {
        #ifdef DEBUG_TRACE_EXECUTION
        for (Value* stack_pointer = vm.stack; stack_pointer < vm.stack_top; stack_pointer++) {
            putchar('[');
            print_value(*stack_pointer);
            putchar(']');
        }
        putchar('\n');

        disassemble_instruction(vm.chunk, (int)(vm.program_counter - vm.chunk->code));
        #endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT:
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            case OP_RETURN:
                print_value(pop());
                return SUCCESSFUL_RUN;
        }

    }

    #undef READ_CONSTANT
    #undef READ_BYTE
}
