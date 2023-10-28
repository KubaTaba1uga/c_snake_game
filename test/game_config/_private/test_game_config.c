/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include "mock_std_lib_interface.h"
#include <stdlib.h>
#include <unity.h>

// App
#include "game_config.c"
#include "game_config.h"
#include <stdio.h>

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_create_game_config(void) {
  game_config_ptr game_config, mocked_memory;

  game_config = NULL, mocked_memory = NULL;

  mocked_memory = malloc(sizeof(struct game_config));

  if (!mocked_memory)
    TEST_FAIL_MESSAGE("Unable to allocate memory for create game config mock.");

  app_malloc_IgnoreAndReturn(mocked_memory);

  game_config = create_game_config();

  TEST_ASSERT_NOT_NULL(game_config);
  TEST_ASSERT_NULL(game_config->users_types);
}
