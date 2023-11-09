/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>
#include <stdlib.h>

// Test framework
#include "game_config/game_config.h"
#include "mock_std_lib_interface.h"
#include <unity.h>

// App
#include "game_config/_private/game_config.c"
#include "game_config/game_difficulty.h"
#include "game_config/game_size.h"

// Test utils
#include "game_config_test_utils.h"

/*******************************************************************************
 *    API
 ******************************************************************************/

size_t game_config_expect_size = 0;

game_config_ptr create_game_config_mock(void) {
  game_config_ptr game_config_mock = NULL;

  game_config_expect_size = sizeof(struct game_config);

  game_config_mock = malloc(game_config_expect_size);

  if (!game_config_mock)
    TEST_FAIL_MESSAGE("Unable to allocate memory for game config mock.");

  return game_config_mock;
}

void destroy_game_config_mock(game_config_ptr game_config_mock) {
  if (game_config_mock) {
    free(game_config_mock);
  }

  game_config_expect_size = 0;
}

void TEST_ASSERT_GAME_DIFFICULTY(game_difficulty_t expected,
                                 game_difficulty_t recived) {

  TEST_ASSERT_EQUAL_STRING(str_game_difficulty(expected),
                           str_game_difficulty(recived));
}

void TEST_ASSERT_GAME_SIZE(game_size_t expected, game_size_t recived) {

  TEST_ASSERT_EQUAL_STRING(str_game_size(expected), str_game_size(recived));
}

void TEST_ASSERT_USER_TYPE(user_type_t expected, user_type_t recived) {

  TEST_ASSERT_EQUAL_STRING(str_user_type(expected), str_user_type(recived));
}
