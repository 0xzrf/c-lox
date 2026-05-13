#include "test_chunk.h"

Chunk chunk;

void setUp(void) {
    init_chunk(&chunk);
}
void tearDown(void) {
    free_chunk(&chunk);
}

static void test_init_chunk(void) {
    TEST_ASSERT_EQUAL(chunk.capacity, 0);
    TEST_ASSERT_EQUAL(chunk.count, 0);
    TEST_ASSERT_EQUAL(chunk.code, NULL);
    TEST_ASSERT_EQUAL(chunk.line_count, 0);
    TEST_ASSERT_EQUAL(chunk.lines, NULL);
}

static void test_write_chunk(void) {

}

void run_chunk_tests(void)  {
    RUN_TEST(test_init_chunk);
}
