/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <endian.h>
#include <stddef.h>

// Test framework
#include <unity.h>

// App
#include "game_config/game_size.h"

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {}
void tearDown() {}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_str_game_size_success(void) {
  char *expected[] = {"Small", "Avarage", "Big"};
  game_size_t input[] = {SMALL, AVARAGE, BIG};
  size_t i;

  for (i = 0; i < sizeof(expected) / sizeof(char *); i++)
    TEST_ASSERT_EQUAL_STRING(expected[i], str_game_size(input[i]));
}

void test_str_game_size_failure(void) {
  game_size_t input[] = {-1, GAME_SIZE_ENUM_LEN};
  size_t i;

  for (i = 0; i < sizeof(input) / sizeof(game_size_t); i++)
    TEST_ASSERT_NULL(str_game_size(input[i]));
}
