#include <stdio.h>

#include "vm.h"
#include "../common/common.h"

VM vm;

void init_vm() {}

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
        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT:
                Value constant = READ_CONSTANT();
                print_value(constant);
                printf("\n");
                break;
            case OP_RETURN:
                return SUCCESSFUL_RUN;
        }

    }

    #undef READ_CONSTANT
    #undef READ_BYTE
}
