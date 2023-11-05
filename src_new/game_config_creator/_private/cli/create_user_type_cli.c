/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// App
#include "../../../game_config/game_config.h"
#include "../../../game_config/user_type.h"
#include "../../../proj_config/constant.h"
#include "../../../proj_config/error.h"
#include "../../../utils/logging_utils.h"
#include "../../../utils/str_utils.h"
#include "utils.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char *valid_user_values[] = {"human", "h", "ai_easy", "ae"};
static const user_type_t user_values_user_type_map[] = {HUMAN, HUMAN, SIMPLE_PC,
                                                        SIMPLE_PC};

/*******************************************************************************
 *    API
 ******************************************************************************/
user_type_t convert_user_input_to_user_type_t(char *user_input) {
  const size_t buffer_size = 255;
  char local_buffer[buffer_size];
  void *received;
  size_t i;

  received = sanitize_user_input(user_input, buffer_size, local_buffer);
  if (!received)
    goto ERROR;

  for (i = 0; i < sizeof(valid_user_values) / sizeof(char *); i++) {

    if (!(are_strs_eq((char *)valid_user_values[i], local_buffer)))
      continue;

    return user_values_user_type_map[i];
  }

ERROR:
  return ENUM_INVALID;
}
