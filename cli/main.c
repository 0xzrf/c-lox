#include "../opcodes/chunk.h"
#include "../debug/debug.h"

int main(int argc, const char *argv[]) {
    Chunk chunk;

    init_chunk(&chunk);


    write_chunk(&chunk, OP_RETURN);
    int constant = add_constant(&chunk, 1.2);
    write_chunk(&chunk, OP_CONSTANT);
    write_chunk(&chunk, constant);
    disassemble_chunk(&chunk, "test chunks");

    free_chunk(&chunk);

    return 0;
}
