/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include <stddef.h>
#include <string.h>
#include <unity.h>

// App
#include "game_config/game_config.h"
#include "game_config/game_size.h"
#include "game_config_creator/_private/cli/create_game_size_cli.c"

// Test utils
#include "../../utils/game_config_test_utils.h"
#include "../../utils/utils_test_utils.h"

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {
  set_up_loggers();
  create_game_config_mock();
}

void tearDown() {
  tear_down_loggers();
  destroy_game_config_mock();
}

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

  TEST_ASSERT_NULL(game_config);
}

void test_create_size_cli_wrong_value(void) {
  game_config_ptr game_config = create_game_config();

  game_config = create_game_size_cli(game_config, "whatever");

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_GAME_SIZE(SMALL, get_game_config_size(game_config));
}

void test_convert_user_input_to_game_size_t_too_long_success(void) {
  const size_t buffer_size = 500;
  const char valid_value[] = "big";

  char user_value[buffer_size];
  game_size_t received;

  strcpy(user_value, valid_value);

  memset(user_value + strlen(user_value), ' ',
         buffer_size - strlen(user_value) - 1);

  user_value[buffer_size - 1] = 0;

  received = convert_user_input_to_game_size_t(user_value);

  TEST_ASSERT_GAME_SIZE(BIG, received);
}
