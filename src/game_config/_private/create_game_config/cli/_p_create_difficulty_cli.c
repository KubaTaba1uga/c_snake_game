/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

// App
#include "../../../../error.h"
#include "../../../../interfaces/std_lib_interface.h"
#include "../../../../user/user_type.h"
#include "../../../../utils/logging_utils.h"
#include "../../../../utils/str_utils.h"
#include "../../../game_difficulty.h"
#include "../../../game_type.h"
#include "../../_p_game_config.h"
#include "_p_create_difficulty_cli.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char *valid_user_values[] = {"easy", "medium", "hard"};
static const game_difficulty_t user_values_difficulty_map[] = {EASY, MEDIUM,
                                                               HARD};
static const char file_id[] = "create_difficulty_cli";
static const game_difficulty_t default_difficulty = EASY;

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
inline game_config_ptr _create_difficulty_cli(game_config_ptr game_config,
                                              char *value);
inline game_difficulty_t
convert_user_input_to_game_difficulty_t(char *user_input);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
game_config_ptr create_difficulty_cli(game_config_ptr game_config,
                                      char *value) {
  game_config_ptr local_game_config;
  errno = 0;

  local_game_config = _create_difficulty_cli(game_config, value);

  if (!local_game_config) {
    switch (errno) {

    case ERROR_NULL_POINTER:
      log_error((char *)file_id, "`value` cannot be `NULL`");
      break;

    case ERROR_GENERIC:
      log_warning(
          (char *)file_id,
          "Cannot create game difficulty based on CLI value `%s`. Setting "
          "default value",
          value);

      set_game_config_difficulty(game_config, default_difficulty);
      local_game_config = game_config;
      break;
    }
  }

  return local_game_config;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
game_config_ptr _create_difficulty_cli(game_config_ptr game_config,
                                       char *value) {
  game_difficulty_t game_difficulty;

  if (!value) {
    errno = ERROR_NULL_POINTER;
    return NULL;
  }

  game_difficulty =
      (game_difficulty_t)convert_user_input_to_game_difficulty_t(value);

  if (game_difficulty == -1) {
    errno = ERROR_GENERIC;
    return NULL;
  }

  set_game_config_difficulty(game_config, game_difficulty);

  return game_config;
}

game_difficulty_t convert_user_input_to_game_difficulty_t(char *user_input) {
  const size_t buffer_size = 255;
  char local_buffer[buffer_size];
  size_t i;
  void *no_err;

  if (strlen(user_input) > buffer_size)
    user_input = cut_str(user_input, buffer_size - 1);

  no_err = strcpy(local_buffer, user_input);
  if (!no_err) {
    goto ERROR;
  }

  lower_str(local_buffer);

  for (i = 0; i < sizeof(valid_user_values) / sizeof(char *); i++) {

    if (!(are_strs_eq((char *)valid_user_values[i], local_buffer)))
      continue;

    return user_values_difficulty_map[i];
  }

ERROR:
  return -1;
}
