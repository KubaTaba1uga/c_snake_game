/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include <stddef.h>
#include <unity.h>

// App
#include "game_config/_private/_p_game_config.h"
#include "game_config/_private/create_game_config/cli/_p_create_difficulty_cli.h"
#include "game_config/game_difficulty.h"
#include "utils/logging_utils.h"

// Test utils
#include "../utils.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/

game_config_ptr game_config_mock = NULL;

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {
  init_loggers();
  create_game_config_mock();
}

void tearDown() {
  destroy_game_config_mock();
  destroy_loggers();
}

void test_create_difficulty_cli_success(void) {
  char *user_value[] = {"easy",   "Easy", "EASY", "medium", "meDIUm",
                        "MEDIUm", "hard", "hard", "HARD"};
  game_difficulty_t expected[] = {EASY,   EASY, EASY, MEDIUM, MEDIUM,
                                  MEDIUM, HARD, HARD, HARD};

  game_config_ptr game_config = create_game_config();
  size_t i;

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {
    game_config = create_difficulty_cli(game_config, user_value[i]);

    TEST_ASSERT_NOT_NULL(game_config);

    TEST_ASSERT_EQUAL(expected[i], get_game_config_difficulty(game_config));
  }
}

void test_create_difficulty_cli_no_value(void) {
  game_config_ptr game_config = create_game_config();

  game_config = create_difficulty_cli(game_config, NULL);

  TEST_ASSERT_NULL(game_config);
}

void test_create_difficulty_cli_wrong_value(void) {
  game_config_ptr game_config = create_game_config();

  game_config = create_difficulty_cli(game_config, "whatever");

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_EQUAL(EASY, get_game_config_difficulty(game_config));
}
