// Test framework
#include "mock_std_lib_interface.h"
#include <stddef.h>
#include <unity.h>

// App
#include "game_config/game_config.h"
#include "game_config/game_difficulty.h"
#include "game_config/game_size.h"
#include "game_config/user_type.h"
#include "game_config_creator/_private/cli/create_game_config_cli.h"

// Test utils
#include "../../utils/game_config_creator_test_utils.h"
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

  create_users_types_mock();
}

void tearDown() {
  destroy_game_config_mock(game_config_mock);
  destroy_users_types_mock();
  tear_down_loggers();
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/

void test_create_game_config_cli_size_short_success(void) {
  char *argv[] = {"exec_path", "-s", "big"};
  int argc = sizeof(argv) / sizeof(char *);

  game_config_ptr game_config;

  game_config = create_game_config();

  game_config = create_game_config_cli(argc, argv, game_config);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_GAME_SIZE(BIG, get_game_config_size(game_config));
}

void test_create_game_config_cli_size_long_success(void) {
  char *argv[] = {"exec_path", "--size", "small"};
  int argc = sizeof(argv) / sizeof(char *);

  game_config_ptr game_config;

  game_config = create_game_config();

  game_config = create_game_config_cli(argc, argv, game_config);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_GAME_SIZE(SMALL, get_game_config_size(game_config));
}

void test_create_game_config_cli_difficulty_short_success(void) {
  char *argv[] = {"exec_path", "-d", "hard"};
  int argc = sizeof(argv) / sizeof(char *);

  game_config_ptr game_config;

  game_config = create_game_config();

  game_config = create_game_config_cli(argc, argv, game_config);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_GAME_DIFFICULTY(HARD, get_game_config_difficulty(game_config));
}

void test_create_game_config_cli_difficulty_long_success(void) {
  char *argv[] = {"exec_path", "--difficulty", "easy"};
  int argc = sizeof(argv) / sizeof(char *);

  game_config_ptr game_config;

  game_config = create_game_config();

  game_config = create_game_config_cli(argc, argv, game_config);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_GAME_DIFFICULTY(EASY, get_game_config_difficulty(game_config));
}

void test_create_game_config_cli_users_types_short_success(void) {
  char *argv[] = {"exec_path", "-u", "human", "-u", "ai_easy"};
  int argc = sizeof(argv) / sizeof(char *);
  user_type_t expected[] = {HUMAN, SIMPLE_PC};

  game_config_ptr game_config;
  user_type_t *received;
  size_t i;

  game_config = create_game_config();

  app_malloc_ExpectAndReturn(users_types_expect_size, users_types_mock);
  game_config = create_game_config_cli(argc, argv, game_config);

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_EQUAL(2, get_game_config_users_amount(game_config));

  received = get_game_config_users_types(game_config);

  TEST_ASSERT_NOT_NULL(received);

  for (i = 0; i < sizeof(expected) / sizeof(user_type_t); i++) {
    TEST_ASSERT_USER_TYPE(expected[i], received[i]);
  }
}

void test_create_game_config_cli_e2e_success(void) {
  char *argv[] = {"exec_path", "-s",    "big", "-d",     "hard",
                  "-u",        "human", "-u",  "ai_easy"};
  int argc = sizeof(argv) / sizeof(char *);
  user_type_t expected_users_types[] = {HUMAN, SIMPLE_PC};

  game_config_ptr game_config;
  size_t i;

  game_config = create_game_config();

  app_malloc_ExpectAndReturn(users_types_expect_size, users_types_mock);
  game_config = create_game_config_cli(argc, argv, game_config);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_EQUAL(BIG, get_game_config_size(game_config));

  TEST_ASSERT_EQUAL(HARD, get_game_config_difficulty(game_config));

  TEST_ASSERT_EQUAL(2, get_game_config_users_amount(game_config));

  TEST_ASSERT_NOT_NULL(get_game_config_users_types(game_config));

  for (i = 0; i < sizeof(expected_users_types) / sizeof(user_type_t); i++) {
    TEST_ASSERT_USER_TYPE(expected_users_types[i],
                          get_game_config_users_types(game_config)[i]);
  }
}
