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
#include "../../../../utils/logging_utils.h"
#include "../../../../utils/str_utils.h"
#include "../../../game_difficulty.h"
#include "../../../game_size.h"
#include "../../_p_game_config.h"
#include "_p_create_size_cli.h"
#include "game_config.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char *valid_user_values[] = {"small", "medium", "big"};
static const game_size_t user_values_game_size_map[] = {SMALL, AVARAGE, BIG};
static const char file_id[] = "create_size_cli";
static const game_size_t default_size = SMALL;

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
inline game_config_ptr _create_size_cli(game_config_ptr game_config,
                                        char *value);
inline game_size_t convert_user_input_to_game_size_t(char *user_input);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
game_config_ptr create_size_cli(game_config_ptr game_config, char *value) {
  game_config_ptr local_game_config;
  errno = 0;

  local_game_config = _create_size_cli(game_config, value);

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
game_config_ptr _create_size_cli(game_config_ptr game_config, char *value) {
  game_size_t game_size;

  if (!value) {
    errno = ERROR_NULL_POINTER;
    return NULL;
  }

  game_size = (game_size_t)convert_user_input_to_game_size_t(value);

  if (game_size == -1) {
    errno = ERROR_GENERIC;
    return NULL;
  }

  set_game_config_size(game_config, game_size);

  return game_config;
}

game_size_t convert_user_input_to_game_size_t(char *user_input) {
  const size_t buffer_size = 255;
  char local_buffer[buffer_size];
  size_t i;
  void *no_err;

  // Cut str
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

    return user_values_game_size_map[i];
  }

ERROR:
  return -1;
}
