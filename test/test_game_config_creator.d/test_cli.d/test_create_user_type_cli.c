/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// Test framework
#include <stddef.h>
#include <string.h>
#include <unity.h>

// App
#include "game_config/game_config.h"
#include "game_config/user_type.h"
#include "game_config_creator/_private/cli/create_user_type_cli.h"
#include "proj_config/constant.h"

// Test utils
#include "../../utils/game_config_test_utils.h"
#include "../../utils/utils_test_utils.h"

/*******************************************************************************
 *    SETUP, TEARDOWN
 ******************************************************************************/
void setUp() { set_up_loggers(); }

void tearDown() { tear_down_loggers(); }

/*******************************************************************************
 *    TEST
 ******************************************************************************/
void test_convert_user_input_to_user_type_t_success(void) {
  char *user_value[] = {"human",   "Human", "HUMAN", "ai_easy", "ai_easy",
                        "Ai_Easy", "h",     "H",     "ae",      "AE"};
  user_type_t expected[] = {HUMAN,     HUMAN, HUMAN, SIMPLE_PC, SIMPLE_PC,
                            SIMPLE_PC, HUMAN, HUMAN, SIMPLE_PC, SIMPLE_PC};

  user_type_t received;
  size_t i;

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {
    received = convert_user_input_to_user_type_t(user_value[i]);

    TEST_ASSERT_NOT_EQUAL(ENUM_INVALID, received);

    TEST_ASSERT_USER_TYPE(expected[i], received);
  }
}

void test_convert_user_input_to_user_type_t_failure(void) {
  char *user_value[] = {"hu",    "Hum", "HUMA", "ai",  "ai_",
                        "Ai_Ea", "hs",  "Hw",   "aew", "AR"};
  user_type_t received;
  size_t i;

  for (i = 0; i < sizeof(user_value) / sizeof(char *); i++) {
    received = convert_user_input_to_user_type_t(user_value[i]);

    TEST_ASSERT_EQUAL(ENUM_INVALID, received);
  }
}
