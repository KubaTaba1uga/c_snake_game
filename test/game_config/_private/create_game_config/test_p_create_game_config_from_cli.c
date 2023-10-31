// Test framework
#include <unity.h>

// App
#include "game_config/_private/_p_game_config.h"
#include "game_config/_private/create_game_config/cli/_p_create_game_config_cli.h"
#include "game_config/game_config.h"
#include "game_config/game_difficulty.h"
#include "game_config/game_type.h"
#include "utils/logging_utils.h"
#include "utils/str_utils.h"

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

void test_create_game_config_cli_size_success(void) {
  int argc = 5;
  char *argv[] = {"exec_path", "-s", "big", "-d", "hard"};

  game_config_ptr game_config;

  /* app_free_Ignore(); */

  game_config = create_game_config_from_cli(argc, argv);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_EQUAL(BIG, get_game_config_size(game_config));
}

void test_create_game_config_cli_size_success_2(void) {
  int argc = 5;
  char *argv[] = {"exec_path ", "-s", "big", "-d", "hard"};

  game_config_ptr game_config;

  app_free_Ignore();

  game_config = create_game_config_from_cli(argc, argv);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_EQUAL(BIG, get_game_config_size(game_config));
}

/* void test_create_game_config_cli_difficulty_success(void) { */
/*   int argc = 3; */
/*   char *argv_[] = {"exec_path", "-s", "big"}; */

/*   game_config_ptr game_config; */

/*   app_free_Ignore(); */

/*   game_config = create_game_config_from_cli(argc, argv_); */

/*   TEST_ASSERT_NOT_NULL(game_config); */

/*   TEST_ASSERT_EQUAL(HARD, get_game_config_difficulty(game_config)); */
/* } */
