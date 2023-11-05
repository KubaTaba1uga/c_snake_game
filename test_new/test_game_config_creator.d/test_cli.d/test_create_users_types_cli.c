/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include <stddef.h>
#include <string.h>
#include <unity.h>

// App
#include "game_config/game_config.h"
#include "game_config/user_type.h"
#include "game_config_creator/_private/cli/create_users_types_cli.h"
#include "proj_config/constant.h"

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

/*******************************************************************************
 *    TEST
 ******************************************************************************/
void test_create_users_types_cli_success(void) {
  char *user_value[] = {"human", "HUMAN", "ai_easy", "ai_easy",
                        "h",     "H",     "ae",      "AE"};
  user_type_t expected[] = {HUMAN, HUMAN, SIMPLE_PC, SIMPLE_PC,
                            HUMAN, HUMAN, SIMPLE_PC, SIMPLE_PC};
  game_config_ptr game_config;
  size_t i;

  game_config = create_game_config();

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {
    game_config = create_users_types_cli(game_config, user_value[i]);

    TEST_ASSERT_NOT_NULL(game_config);

    TEST_ASSERT_USER_TYPE(expected[i],
                          get_game_config_users_types(game_config)[i]);
  }
}
