/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// Test framework
#include <unity.h>

// App
#include "game_config/user_type.h"

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() {}
void tearDown() {}

/*******************************************************************************
 *    TESTS
 ******************************************************************************/
void test_str_user_type_success(void) {
  char *expected[] = {"Human", "EasyPc", "LanServer", "LanClient"};
  user_type_t input[] = {HUMAN, SIMPLE_PC, LAN_SERVER, LAN_CLIENT};
  size_t i;

  for (i = 0; i < sizeof(expected) / sizeof(char *); i++)
    TEST_ASSERT_EQUAL_STRING(expected[i], str_user_type(input[i]));
}

void test_str_user_type_failure(void) {
  user_type_t input[] = {-1, USER_TYPE_ENUM_LEN};
  size_t i;

  for (i = 0; i < sizeof(input) / sizeof(user_type_t); i++)
    TEST_ASSERT_NULL(str_user_type(input[i]));
}
