#include <stdio.h>
#include <stdlib.h>

#include "vm_helpers.h"
#include "vm.h"
#include "../common/common.h"
#include "../debug/debug.h"

VM vm;

void init_vm() {
    init_stack();
}

// intialize stack_top to be = stack, that means the stack is empty
void init_stack() {
    vm.stack_size = INIT_MAX_STACK_SIZE;
    vm.stack_top = vm.stack = realloc(vm.stack, vm.stack_size);
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

Value pop() {
    return *--vm.stack_top; // decrement vm.stack_top first, and then dereference it
}

void free_vm() {}

InterpreterResult interpret(const char* source) {
    compile(source);
    return SUCCESSFUL_RUN;
}

static InterpreterResult run() {
    #define READ_BYTE() (*vm.program_counter++)
    #define READ_CONSTANT() (vm.chunk->constants.value[READ_BYTE()])
    #define BINARY_OP(op) \
        do { \
            Value b = pop();    \
            Value a = pop();    \
            push(a op b);      \
        } while (false) \

    INFINITE_LOOP {
        #ifdef DEBUG_TRACE_EXECUTION
        for (Value* stack_pointer = vm.stack; stack_pointer < vm.stack_top; stack_pointer++) {
            putchar('[');
            print_value(*stack_pointer, 0);
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
            case OP_ADD: BINARY_OP(+); break;
            case OP_SUB: BINARY_OP(-); break;
            case OP_MUL: BINARY_OP(*); break;
            case OP_DIV: BINARY_OP(/); break;
            case OP_NEGATE: _negate_last_stack_var(&vm); break;
            case OP_RETURN:
                print_value(pop(), 1);
                return SUCCESSFUL_RUN;
        }

    }

    #undef READ_CONSTANT
    #undef READ_BYTE
    #undef BINARY_OP
}
