/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include "mock_std_lib_interface.h"
#include <stddef.h>
#include <stdlib.h>
#include <unity.h>

// App
#include "game_config.c"
#include "game_config.h"
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
