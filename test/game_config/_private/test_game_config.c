/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include "game_size.h"
#include "mock_std_lib_interface.h"
#include <stddef.h>
#include <stdlib.h>
#include <unity.h>

// App
#include "game_config.c"
#include "game_config.h"
#include "game_difficulty.h"
#include "game_type.h"
#include "user_type.h"
#include <stdio.h>

game_config_ptr game_config_mock = NULL;

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {
  size_t game_config_size;

  game_config_mock = NULL;

  game_config_size = sizeof(struct game_config);

  game_config_mock = malloc(game_config_size);

  if (!game_config_mock)
    TEST_FAIL_MESSAGE("Unable to allocate memory for game config mock.");

  app_malloc_ExpectAndReturn(game_config_size, game_config_mock);
}

void tearDown() {
  if (game_config_mock)
    free(game_config_mock);
}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_create_game_config(void) {
  game_config_ptr game_config;

  game_config = NULL;

  game_config = create_game_config();

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_NULL(game_config->users_types);
}

void test_destroy_game_config(void) {
  game_config_ptr game_config;

  game_config = create_game_config();

  app_free_Expect(game_config);

  destroy_game_config(game_config);
}

void test_get_game_config_type(void) {
  game_config_ptr game_config;
  game_type_t game_type;

  game_config = create_game_config();

  game_config->type = LOCAL;

  game_type = get_game_config_type(game_config);

  TEST_ASSERT_EQUAL_MESSAGE(LOCAL, game_type, "Game type should be LOCAL");
}

void test_get_game_config_difficulty(void) {
  game_config_ptr game_config;
  game_difficulty_t game_difficulty;

  game_config = create_game_config();

  game_config->difficulty = EASY;

  game_difficulty = get_game_config_difficulty(game_config);

  TEST_ASSERT_EQUAL_MESSAGE(EASY, game_difficulty,
                            "Game difficulty should be EASY");
}

void test_get_game_config_size(void) {
  game_config_ptr game_config;
  game_size_t game_size;

  game_config = create_game_config();

  game_config->size = SMALL;

  game_size = get_game_config_size(game_config);

  TEST_ASSERT_EQUAL_MESSAGE(SMALL, game_size, "Game size should be SMALL");
}

void test_get_game_config_users_amount(void) {
  game_config_ptr game_config;
  size_t users_amount;

  game_config = create_game_config();

  game_config->users_amount = 5;

  users_amount = get_game_config_users_amount(game_config);

  TEST_ASSERT_EQUAL_MESSAGE(5, users_amount, "Users amount should be 5");
}

void test_get_game_config_users_types(void) {
  game_config_ptr game_config;
  user_type_t *users_types;

  user_type_t expected_users_types[] = {HUMAN};

  game_config = create_game_config();

  game_config->users_types = expected_users_types;

  users_types = get_game_config_users_types(game_config);

  TEST_ASSERT_EQUAL_MESSAGE(expected_users_types, users_types,
                            "Users types should be {HUMAN}");
}
