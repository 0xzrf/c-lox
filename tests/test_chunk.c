#include "test_chunk.h"

void setUp(void) {}
void tearDown(void) {}

static void test_init_chunk(void) {
    Chunk chunk;

    init_chunk(&chunk);

    TEST_ASSERT_EQUAL(chunk.capacity, 0);
    TEST_ASSERT_EQUAL(chunk.count, 0);
    TEST_ASSERT_EQUAL(chunk.code, NULL);
    TEST_ASSERT_EQUAL(chunk.line_count, 0);
    TEST_ASSERT_EQUAL(chunk.lines, NULL);
}

void run_chunk_tests(void)  {
    RUN_TEST(test_init_chunk);
}
