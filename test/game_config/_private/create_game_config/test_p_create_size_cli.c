/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include <unity.h>

// App
#include "game_config/_private/_p_game_config.h"
#include "game_config/_private/create_game_config/cli/_p_create_size_cli.h"
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

void test_create_size_cli_success(void) {
  game_config_ptr game_config = create_game_config();
  char user_value[] = "small";

  game_config = create_size_cli(game_config, user_value);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_EQUAL(SMALL, get_game_config_size(game_config));
  /* TEST_ASSERT_EQUAL(EASY, get_game_config_difficulty(game_config)); */
}
