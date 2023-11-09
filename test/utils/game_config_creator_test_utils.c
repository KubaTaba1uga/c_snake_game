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
size_t max_users_amount = 8;
size_t users_types_expect_size = 0;

void create_users_types_mock(void) {
  static const size_t mock_length = 100;

  users_types_expect_size = max_users_amount * sizeof(user_type_t);

  users_types_mock = malloc(mock_length * sizeof(user_type_t));

  if (!users_types_mock)
    TEST_FAIL_MESSAGE("Unable to allocate memory for users types mock");
}

void destroy_users_types_mock(void) {
  if (users_types_mock)
    free(users_types_mock);

  users_types_mock = NULL;
}
