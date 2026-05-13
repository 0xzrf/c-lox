#include <stdio.h>

#include "../opcodes/chunk.h"
#include "../vm/vm.h"

int main(int argc, const char *argv[]) {
    init_vm();

    Chunk chunk;

    init_chunk(&chunk);

    write_chunk(&chunk, OP_CONSTANT, 2);
    int constant = add_constant(&chunk, 1.2);
    write_chunk(&chunk, constant, 2);

    constant = add_constant(&chunk, 3.6);
    write_chunk(&chunk, OP_CONSTANT, 2);
    write_chunk(&chunk, constant, 2);

    write_chunk(&chunk, OP_ADD, 2);

    constant = add_constant(&chunk, 5.4);
    write_chunk(&chunk, OP_CONSTANT, 2);
    write_chunk(&chunk, constant, 2);

    write_chunk(&chunk, OP_DIV, 2);

    // write_chunk(&chunk, OP_NEGATE, 3);

    write_chunk(&chunk, OP_RETURN, 1);
    interpret(&chunk);

    free_chunk(&chunk);
    free_vm();

    return 0;
}
