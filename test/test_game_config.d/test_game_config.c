/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

// Test framework
#include "mock_std_lib_interface.h"
#include <unity.h>

// App
#include "game_config/_private/game_config.c"
#include "game_config/game_config.h"
#include "game_config/game_difficulty.h"
#include "game_config/game_size.h"
#include "game_config/user_type.h"
#include "proj_config/constant.h"

// Test utils
#include "../utils/game_config_test_utils.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static game_config_ptr game_config_mock;

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {
  game_config_mock = create_game_config_mock();
  app_malloc_ExpectAndReturn(game_config_expect_size, game_config_mock);
}

void tearDown() { destroy_game_config_mock(game_config_mock); }

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_create_game_config(void) {
  game_config_ptr game_config;

  game_config = NULL;

  game_config = create_game_config();

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_NULL(game_config->users_types);
  TEST_ASSERT_EQUAL(0, game_config->users_amount);
  TEST_ASSERT_EQUAL(ENUM_INVALID, game_config->size);
  TEST_ASSERT_EQUAL(ENUM_INVALID, game_config->difficulty);
}

void test_destroy_game_config(void) {
  game_config_ptr game_config;

  game_config = create_game_config();

  app_free_Expect(game_config);

  destroy_game_config(game_config);
}

void test_get_game_config_difficulty(void) {
  game_config_ptr game_config;
  game_difficulty_t game_difficulty;

  game_config = create_game_config();

  game_config->difficulty = EASY;

  game_difficulty = get_game_config_difficulty(game_config);

  TEST_ASSERT_GAME_DIFFICULTY(EASY, game_difficulty);
}

void test_get_game_config_size(void) {
  game_config_ptr game_config;
  game_size_t game_size;

  game_config = create_game_config();

  game_config->size = BIG;

  game_size = get_game_config_size(game_config);

  TEST_ASSERT_GAME_SIZE(BIG, game_size);
}

void test_get_game_config_users_amount(void) {
  game_config_ptr game_config;
  size_t users_amount;

  game_config = create_game_config();

  game_config->users_amount = 5;

  users_amount = get_game_config_users_amount(game_config);

  TEST_ASSERT_EQUAL(5, users_amount);
}

void test_get_game_config_users_types(void) {
  user_type_t expected_users_types[] = {HUMAN};
  game_config_ptr game_config;
  user_type_t *users_types;
  size_t i;

  game_config = create_game_config();

  game_config->users_types = expected_users_types;

  users_types = get_game_config_users_types(game_config);

  for (i = 0; i < sizeof(expected_users_types) / sizeof(user_type_t); i++)
    TEST_ASSERT_USER_TYPE(expected_users_types[i], users_types[i]);
}

void test_set_game_config_difficulty(void) {
  game_config_ptr game_config;

  game_config = create_game_config();

  set_game_config_difficulty(game_config, EASY);

  TEST_ASSERT_GAME_DIFFICULTY(EASY, game_config->difficulty);
}

void test_set_game_config_size(void) {
  game_config_ptr game_config;

  game_config = create_game_config();

  set_game_config_size(game_config, BIG);

  TEST_ASSERT_GAME_SIZE(BIG, game_config->size);
}

void test_set_game_config_users_types(void) {
  game_config_ptr game_config;
  user_type_t expected_users_types[] = {HUMAN, HUMAN, HUMAN};
  size_t expected_users_amount =
      sizeof(expected_users_types) / sizeof(user_type_t);
  size_t i;

  game_config = create_game_config();

  set_game_config_users_types(game_config, expected_users_amount,
                              expected_users_types);

  TEST_ASSERT_EQUAL(expected_users_amount, game_config->users_amount);

  for (i = 0; i < expected_users_amount; i++)
    TEST_ASSERT_USER_TYPE(expected_users_types[i], game_config->users_types[i]);
}
