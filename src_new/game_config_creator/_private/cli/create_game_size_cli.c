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
#include "../../../game_config/game_size.h"
#include "../../../proj_config/constant.h"
#include "../../../proj_config/error.h"
#include "../../../utils/logging_utils.h"
#include "../../../utils/str_utils.h"
#include "utils.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char file_id[] = "create_game_size_cli";
static const char *valid_user_values[] = {"small", "medium", "big"};
static const game_size_t user_values_game_size_map[] = {SMALL, AVARAGE, BIG};
static const game_size_t default_size = SMALL;

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
inline game_config_ptr _create_game_size_cli(game_config_ptr game_config,
                                             char *value);
inline game_size_t convert_user_input_to_game_size_t(char *user_input);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
game_config_ptr create_game_size_cli(game_config_ptr game_config, char *value) {
  game_config_ptr local_game_config;

  errno = 0;

  local_game_config = _create_game_size_cli(game_config, value);

  if (!local_game_config) {
    switch (errno) {

    case ERROR_NULL_POINTER:
      log_error((char *)file_id, "`value` cannot be `NULL`");
      break;

    case ERROR_GENERIC:
      log_warning((char *)file_id,
                  "Cannot create game size based on CLI value `%s`. Setting "
                  "default value",
                  value);

      set_game_config_size(game_config, default_size);
      local_game_config = game_config;
      break;
    }
  }

  return local_game_config;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
game_config_ptr _create_game_size_cli(game_config_ptr game_config,
                                      char *value) {
  game_size_t game_size;

  if (!value) {
    errno = ERROR_NULL_POINTER;
    goto ERROR;
  }

  game_size = (game_size_t)convert_user_input_to_game_size_t(value);

  if ((int)game_size == ENUM_INVALID) {
    errno = ERROR_GENERIC;
    goto ERROR;
  }

  set_game_config_size(game_config, game_size);

  return game_config;

ERROR:
  return NULL;
}

game_size_t convert_user_input_to_game_size_t(char *user_input) {
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

    return user_values_game_size_map[i];
  }

ERROR:
  return ENUM_INVALID;
}
