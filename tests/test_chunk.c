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
    const int LINE_NUMBER = 1;
    write_chunk(&chunk, OP_ADD, LINE_NUMBER);

    TEST_ASSERT_EQUAL( chunk.capacity, MIN_CAP);
    TEST_ASSERT_EQUAL(chunk.line_count, MIN_CAP);
    TEST_ASSERT_EQUAL(chunk.lines[LINE_NUMBER], 1);
    TEST_ASSERT_EQUAL( chunk.count, 1);
    TEST_ASSERT_EQUAL(*chunk.code, OP_ADD);
}

void run_chunk_tests(void)  {
    RUN_TEST(test_init_chunk);
    RUN_TEST(test_write_chunk);
}
