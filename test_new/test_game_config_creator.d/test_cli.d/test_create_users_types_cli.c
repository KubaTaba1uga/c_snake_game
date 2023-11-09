/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <errno.h>
#include <stddef.h>
#include <string.h>

// Test framework
#include "mock_std_lib_interface.h"
#include <unity.h>

// App
#include "game_config/game_config.h"
#include "game_config/user_type.h"
#include "game_config_creator/_private/cli/create_users_types_cli.h"
#include "proj_config/constant.h"
#include "proj_config/error.h"

// Test utils
#include "../../utils/game_config_creator_test_utils.h"
#include "../../utils/game_config_test_utils.h"
#include "../../utils/utils_test_utils.h"

static game_config_ptr game_config_mock;

void setUp() {
  set_up_loggers();

  game_config_mock = create_game_config_mock();

  create_users_types_mock();
}

void tearDown() {
  destroy_game_config_mock(game_config_mock);
  destroy_users_types_mock();
  tear_down_loggers();
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
  user_type_t *users_types;
  size_t i;

  app_malloc_ExpectAndReturn(game_config_expect_size, game_config_mock);

  game_config = create_game_config();

  app_malloc_ExpectAndReturn(users_types_expect_size, users_types_mock);

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {

    game_config = create_users_types_cli(game_config, user_value[i]);
    users_types = get_game_config_users_types(game_config);

    TEST_ASSERT_NOT_NULL(game_config);
    TEST_ASSERT_EQUAL(i + 1, get_game_config_users_amount(game_config));
    TEST_ASSERT_USER_TYPE(expected[i], users_types[i]);
  }
}

void test_create_users_types_cli_failure_wrong_value(void) {
  char user_value[] = {"whatever"};
  game_config_ptr game_config, received;

  app_malloc_ExpectAndReturn(game_config_expect_size, game_config_mock);

  game_config = create_game_config();

  received = create_users_types_cli(game_config, user_value);

  TEST_ASSERT_NULL(received);
  TEST_ASSERT_NULL(get_game_config_users_types(game_config));
  TEST_ASSERT_EQUAL(0, get_game_config_users_amount(game_config));
  TEST_ASSERT_EQUAL(ERROR_INVALID_USER_INPUT, errno);
}

void test_create_users_types_cli_failure_too_many_players(void) {
  char *user_value[] = {"human", "HUMAN", "ai_easy", "ai_easy", "h",
                        "H",     "ae",    "AE",      "h",       "h"};
  game_config_ptr game_config, received;
  size_t i;

  app_malloc_ExpectAndReturn(game_config_expect_size, game_config_mock);

  game_config = create_game_config();

  app_malloc_ExpectAndReturn(users_types_expect_size, users_types_mock);
  app_free_Expect(users_types_mock);

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {
    received = create_users_types_cli(game_config, user_value[i]);
  }

  TEST_ASSERT_NULL(received);
  TEST_ASSERT_NULL(get_game_config_users_types(game_config));
  TEST_ASSERT_EQUAL(0, get_game_config_users_amount(game_config));
  TEST_ASSERT_EQUAL(ERROR_TOO_MANY_USERS, errno);
}

void test_create_users_types_cli_failure_oom(void) {
  char user_value[] = {"human"};
  game_config_ptr game_config, received;

  app_malloc_ExpectAndReturn(game_config_expect_size, game_config_mock);

  game_config = create_game_config();

  app_malloc_IgnoreAndReturn(NULL);

  received = create_users_types_cli(game_config, user_value);

  app_malloc_StopIgnore();

  TEST_ASSERT_NULL(received);
  TEST_ASSERT_NULL(get_game_config_users_types(game_config));
  TEST_ASSERT_EQUAL(0, get_game_config_users_amount(game_config));
  TEST_ASSERT_EQUAL(ERROR_OOM, errno);
}
