#include <stdio.h>

#include "vm.h"
#include "../common/common.h"
#include "../debug/debug.h"

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
        #ifdef DEBUG_TRACE_EXECUTION
        disassemble_instruction(vm.chunk, (int)(vm.program_counter - vm.chunk->code));
        #endif

        uint8_t instruction;
        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT:
                Value constant;
                constant = READ_CONSTANT();
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
