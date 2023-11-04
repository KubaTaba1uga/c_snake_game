#include "game_config/game_type.h"
#include <stddef.h>
#include <unity.h>

void setUp() {}
void tearDown() {}

void test_str_game_type_success(void) {
  char *expected[] = {"Local", "Server", "Client"};
  game_type_t input[] = {LOCAL, SERVER, CLIENT};
  size_t i;

  for (i = 0; i < sizeof(expected) / sizeof(char *); i++)
    TEST_ASSERT_EQUAL_STRING(expected[i], str_game_type(input[i]));
}

void test_str_game_type_failure(void) {
  game_type_t input[] = {-1, GAME_TYPE_ENUM_LEN};
  size_t i;

  for (i = 0; i < sizeof(input) / sizeof(game_type_t); i++)
    TEST_ASSERT_NULL(str_game_type(input[i]));
}
