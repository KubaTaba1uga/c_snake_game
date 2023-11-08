/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include "mock_std_lib_interface.h"
#include <stddef.h>
#include <string.h>
#include <unity.h>

// App
#include "game_config/game_config.h"
#include "game_config/game_difficulty.h"
#include "game_config_creator/_private/cli/create_game_difficulty_cli.h"

// Test utils
#include "../../utils/game_config_test_utils.h"
#include "../../utils/utils_test_utils.h"

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {
  set_up_loggers();

  create_game_config_mock();
  app_malloc_ExpectAndReturn(game_config_expect_size, game_config_mock);
}

void tearDown() {
  tear_down_loggers();
  destroy_game_config_mock();
}

/*******************************************************************************
 *    TEST
 ******************************************************************************/
void test_create_difficulty_cli_success(void) {
  char *user_value[] = {"easy",   "Easy", "EASY", "medium", "meDIUm",
                        "MEDIUm", "hard", "hard", "HARD"};

  game_difficulty_t expected[] = {EASY,   EASY, EASY, MEDIUM, MEDIUM,
                                  MEDIUM, HARD, HARD, HARD};

  game_config_ptr game_config = create_game_config();
  size_t i;

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {
    game_config = create_game_difficulty_cli(game_config, user_value[i]);

    TEST_ASSERT_NOT_NULL(game_config);

    TEST_ASSERT_GAME_DIFFICULTY(expected[i],
                                get_game_config_difficulty(game_config));
  }
}

void test_create_difficulty_cli_no_value(void) {
  game_config_ptr game_config = create_game_config();

  game_config = create_game_difficulty_cli(game_config, NULL);

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_GAME_DIFFICULTY(EASY, get_game_config_difficulty(game_config));
}

void test_create_difficulty_cli_wrong_value(void) {
  game_config_ptr game_config = create_game_config();

  game_config = create_game_difficulty_cli(game_config, "whatever");

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_GAME_DIFFICULTY(EASY, get_game_config_difficulty(game_config));
}
