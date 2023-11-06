/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// Test framework
#include "mock_std_lib_interface.h"
#include <stdlib.h>
#include <unity.h>

// App
#include "game_config/user_type.h"

#include "game_config_creator_test_utils.h"
/*******************************************************************************
 *    API
 ******************************************************************************/
user_type_t *users_types_mock = NULL;

void create_users_types_mock(void) {
  static const size_t mock_length = 100;
  static const size_t max_users_amount = 8;

  user_type_t *mock = malloc(mock_length * sizeof(user_type_t));

  if (!mock)
    TEST_FAIL_MESSAGE("Unable to allocate memory for users types mock");

  users_types_mock = mock;

  app_malloc_ExpectAndReturn(max_users_amount * sizeof(user_type_t),
                             users_types_mock);
}

void destroy_users_types_mock(void) {
  if (users_types_mock)
    free(users_types_mock);

  users_types_mock = NULL;
}
