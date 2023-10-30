// Test framework
#include <unity.h>

// App
#include "_p_create_game_config_cli.c"
#include "_p_game_config.h"
#include "game_config.h"
#include "game_difficulty.h"
#include "game_type.h"
#include "logging_utils.h"
#include "str_utils.h"

// Test utils
#include "../utils.h"
#include "mock_std_lib_interface.h"

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

/*******************************************************************************
 *    TESTS
 ******************************************************************************/

void test_create_game_config_from_cli_success(void) {
  int argc = 3;
  char *argv[] = {"exec_path", "-s", "small"};

  game_config_ptr game_config;

  app_free_Ignore();

  game_config = create_game_config_from_cli(argc, argv);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_EQUAL(SMALL, get_game_config_size(game_config));
  /* TEST_ASSERT_EQUAL(EASY, get_game_config_difficulty(game_config)); */
}
