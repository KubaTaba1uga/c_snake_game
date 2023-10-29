// Test framework
#include <unity.h>

// App
#include "_p_create_game_config_from_cli.c"
#include "_p_game_config.h"
#include "logging_utils.h"

// Test utils
#include "utils.h"

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
  char *argv[] = {"exec_path", "-d", "aLLkdjakljdlkasjdlk"};

  game_config_ptr game_config;

  game_config = create_game_config_from_cli(argc, argv);

  TEST_ASSERT_NOT_NULL(game_config);
}
