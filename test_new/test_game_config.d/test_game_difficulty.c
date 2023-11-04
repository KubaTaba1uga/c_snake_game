/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// Test framework
#include <unity.h>

// App
#include "game_config/game_difficulty.h"

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {}
void tearDown() {}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_str_game_difficulty_success(void) {
  char *expected[] = {"Easy", "Medium", "Hard"};
  game_difficulty_t input[] = {EASY, MEDIUM, HARD};
  size_t i;

  for (i = 0; i < sizeof(expected) / sizeof(char *); i++)
    TEST_ASSERT_EQUAL_STRING(expected[i], str_game_difficulty(input[i]));
}

void test_str_game_difficulty_failure(void) {
  game_difficulty_t input[] = {-1, GAME_DIFFICULTY_ENUM_LEN};
  size_t i;

  for (i = 0; i < sizeof(input) / sizeof(game_difficulty_t); i++)
    TEST_ASSERT_NULL(str_game_difficulty(input[i]));
}
