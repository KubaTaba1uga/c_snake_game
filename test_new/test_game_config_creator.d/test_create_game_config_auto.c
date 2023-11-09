#include "game_config/game_difficulty.h"
#include "game_config/game_size.h"
#include "game_config/user_type.h"
#include "mock_std_lib_interface.h"
#include <unity.h>

#include "game_config/game_config.h"
#include "game_config_creator/game_config_creator.h"

// Test utils
#include "../utils/game_config_creator_test_utils.h"
#include "../utils/game_config_test_utils.h"
#include "../utils/utils_test_utils.h"
#include "test_cli.d/test_create_game_config_cli.p/mock_std_lib_interface.h"

static game_config_ptr game_config_mock;

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

void test_create_game_config_auto_success(void) {
  char *argv[] = {"exec_path", "--size", " medium ", "-d",
                  "medium",    "--user", "human",    "-u",
                  " h ",       "--user", "ai_easy"};
  int argc = sizeof(argv) / sizeof(char *);
  user_type_t expected_users_types[] = {HUMAN, HUMAN, SIMPLE_PC};

  game_config_ptr game_config;
  size_t i;

  app_malloc_ExpectAndReturn(users_types_expect_size, users_types_mock);

  game_config = create_game_config_auto(argc, argv);

  TEST_ASSERT_NOT_NULL(game_config);

  TEST_ASSERT_GAME_SIZE(AVARAGE, get_game_config_size(game_config));

  TEST_ASSERT_GAME_DIFFICULTY(MEDIUM, get_game_config_difficulty(game_config));

  TEST_ASSERT_EQUAL(3, get_game_config_users_amount(game_config));

  TEST_ASSERT_NOT_NULL(get_game_config_users_types(game_config));

  for (i = 0; i < sizeof(expected_users_types) / sizeof(user_type_t); i++) {
    TEST_ASSERT_USER_TYPE(expected_users_types[i],
                          get_game_config_users_types(game_config)[i]);
  }
}

void test_create_game_config_auto_all_failed_failure(void) {
  char *argv[] = {"exec_path", "-u"};
  int argc = sizeof(argv) / sizeof(char *);

  game_config_ptr game_config;

  app_free_Expect(game_config_mock);

  game_config = create_game_config_auto(argc, argv);

  TEST_ASSERT_NULL(game_config);
}

void test_create_game_config_auto_validation_failure(void) {
  char *argv[] = {"exec_path"};
  int argc = sizeof(argv) / sizeof(char *);

  game_config_ptr game_config;

  app_free_Expect(game_config_mock);

  game_config = create_game_config_auto(argc, argv);

  TEST_ASSERT_NULL(game_config);
}
