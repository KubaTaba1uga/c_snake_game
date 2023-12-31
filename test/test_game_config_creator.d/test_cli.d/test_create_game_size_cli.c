/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include <stddef.h>
#include <string.h>

// Test framework
#include "mock_std_lib_interface.h"
#include <unity.h>

// App
#include "game_config/game_config.h"
#include "game_config/game_size.h"
#include "game_config_creator/_private/cli/create_game_size_cli.h"

// Test utils
#include "../../utils/game_config_test_utils.h"
#include "../../utils/utils_test_utils.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static game_config_ptr game_config_mock;

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {
  set_up_loggers();

  game_config_mock = create_game_config_mock();
  app_malloc_ExpectAndReturn(game_config_expect_size, game_config_mock);
}

void tearDown() {
  destroy_game_config_mock(game_config_mock);

  tear_down_loggers();
}

/*******************************************************************************
 *    TEST
 ******************************************************************************/
void test_create_size_cli_success(void) {
  char *user_value[] = {"small",  "Small", "SMALL", "medium", "meDIUm",
                        "MEDIUm", "big",   "bIg",   "BIG"};
  game_size_t expected[] = {SMALL,   SMALL, SMALL, AVARAGE, AVARAGE,
                            AVARAGE, BIG,   BIG,   BIG};

  game_config_ptr game_config = create_game_config();
  size_t i;

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {
    game_config = create_game_size_cli(game_config, user_value[i]);

    TEST_ASSERT_NOT_NULL(game_config);

    TEST_ASSERT_GAME_SIZE(expected[i], get_game_config_size(game_config));
  }
}

void test_create_size_cli_no_value(void) {
  game_config_ptr game_config = create_game_config();

  game_config = create_game_size_cli(game_config, NULL);

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_GAME_SIZE(SMALL, get_game_config_size(game_config));
}

void test_create_size_cli_wrong_value(void) {
  game_config_ptr game_config = create_game_config();

  game_config = create_game_size_cli(game_config, "whatever");

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_GAME_SIZE(SMALL, get_game_config_size(game_config));
}
