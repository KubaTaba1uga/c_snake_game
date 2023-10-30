/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stdlib.h>

// Test framework
#include "mock_std_lib_interface.h"
#include <unity.h>

// App
#include "game_config/_private/game_config.c"

// Test utils
#include "utils.h"

/*******************************************************************************
 *    API
 ******************************************************************************/

void create_game_config_mock(void) {
  size_t game_config_size;

  game_config_mock = NULL;

  game_config_size = sizeof(struct game_config);

  game_config_mock = malloc(game_config_size);

  if (!game_config_mock)
    TEST_FAIL_MESSAGE("Unable to allocate memory for game config mock.");

  app_malloc_ExpectAndReturn(game_config_size, game_config_mock);
}

void destroy_game_config_mock(void) {
  if (game_config_mock)
    free(game_config_mock);
}
