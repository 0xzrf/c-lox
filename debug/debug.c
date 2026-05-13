#include <stdint.h>
#include <stdio.h>
#include "debug.h"
#include "../constants/value.h"

void disassemble_chunk(Chunk *chunk, const char *name) {
    printf("=== %s ===\n", name);

    for (int offset = 0; offset < chunk->count;) {
        offset = disassemble_instruction(chunk, offset);
    }
}

int disassemble_instruction(Chunk *chunk, int offset) {
    printf("%04d ", offset);

    printf("%4d ", get_line(chunk, offset + 1));

    uint8_t instruction = chunk->code[offset];

    switch (instruction) {
        case OP_RETURN:
            return simple_instruction("OP_RETURN", offset);
        case OP_NEGATE:
            return simple_instruction("OP_NEGATE", offset);
        case OP_ADD:
            return simple_instruction("OP_ADD", offset);
        case OP_SUB:
            return simple_instruction("OP_SUB", offset);
        case OP_MUL:
            return simple_instruction("OP_MUL", offset);
        case OP_DIV:
            return simple_instruction("OP_DIV", offset);
        case OP_CONSTANT:
            return constant_instruction("OP_CONSTANT", chunk, offset);
        default:
            printf("Unknown Opecode %d\n", instruction);
            return offset + 1;
    }
}

static int simple_instruction(const char * name, int offset) {
    printf("%s\n", name);
    return offset + 1;
}

static int constant_instruction(const char * name, Chunk * chunk, int offset) {
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d ", name, constant);
    print_value(chunk->constants.value[constant], 1);
    return offset + 2;
}
