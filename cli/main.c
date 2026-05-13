#include <stdio.h>

#include "../opcodes/chunk.h"
#include "../debug/debug.h"
#include "../vm/vm.h"

int main(int argc, const char *argv[]) {
    init_vm();

    Chunk chunk;

    init_chunk(&chunk);

    write_chunk(&chunk, OP_RETURN, 1);
    int constant = add_constant(&chunk, 1.2);

    write_chunk(&chunk, OP_CONSTANT, 2);
    write_chunk(&chunk, constant, 2);

    disassemble_chunk(&chunk, "test chunks");

    free_chunk(&chunk);
    free_vm();

    return 0;
}
