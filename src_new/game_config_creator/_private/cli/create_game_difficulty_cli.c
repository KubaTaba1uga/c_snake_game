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
#include "../../../game_config/game_difficulty.h"
#include "../../../proj_config/constant.h"
#include "../../../proj_config/error.h"
#include "../../../utils/logging_utils.h"
#include "../../../utils/str_utils.h"
#include "utils.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char file_id[] = "create_game_difficulty_cli";
static const char *valid_user_values[] = {"easy", "medium", "hard"};
static const game_difficulty_t user_values_difficulty_map[] = {EASY, MEDIUM,
                                                               HARD};
static const game_difficulty_t default_difficulty = EASY;

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
inline game_config_ptr _create_game_difficulty_cli(game_config_ptr game_config,
                                                   char *value);
inline game_difficulty_t
convert_user_input_to_game_difficulty_t(char *user_input);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
game_config_ptr create_game_difficulty_cli(game_config_ptr game_config,
                                           char *value) {
  game_config_ptr local_game_config;

  errno = 0;

  local_game_config = _create_game_difficulty_cli(game_config, value);

  if (!local_game_config) {

    switch (errno) {

    case ERROR_INVALID_USER_INPUT:

      log_warning(
          (char *)file_id,
          "Cannot create game difficulty based on CLI value `%s`. Setting "
          "default value: EASY.",
          value);

      set_game_config_difficulty(game_config, default_difficulty);
      local_game_config = game_config;
      break;

    default:
      log_error((char *)file_id, "Unknown errno value %i", errno);
    }
  }

  return local_game_config;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
game_config_ptr _create_game_difficulty_cli(game_config_ptr game_config,
                                            char *value) {
  game_difficulty_t game_difficulty;

  if (!value) {
    errno = ERROR_INVALID_USER_INPUT;
    return NULL;
  }

  game_difficulty =
      (game_difficulty_t)convert_user_input_to_game_difficulty_t(value);

  if (game_difficulty == ENUM_INVALID) {
    errno = ERROR_INVALID_USER_INPUT;
    return NULL;
  }

  set_game_config_difficulty(game_config, game_difficulty);

  return game_config;
}

game_difficulty_t convert_user_input_to_game_difficulty_t(char *user_input) {
  const size_t buffer_size = 255;
  char local_buffer[buffer_size];
  size_t i;
  void *received;

  received = sanitize_user_input(user_input, buffer_size, local_buffer);

  if (!received) {
    goto ERROR;
  }

  for (i = 0; i < sizeof(valid_user_values) / sizeof(char *); i++) {

    if (!(are_strs_eq((char *)valid_user_values[i], local_buffer)))
      continue;

    return user_values_difficulty_map[i];
  }

ERROR:
  return ENUM_INVALID;
}
