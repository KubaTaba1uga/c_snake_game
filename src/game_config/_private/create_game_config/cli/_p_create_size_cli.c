#include "_p_create_size_cli.h"
#include "../../../../utils/str_utils.h"
#include "_p_game_config.h"
#include "game_difficulty.h"
#include "game_size.h"
#include "std_lib_interface.h"
/* #include "str_utils.h" */
#include <stddef.h>
#include <string.h>

const char *valid_user_values[] = {"small", "medium", "big"};
const game_size_t user_values_game_size_map[] = {SMALL, AVARAGE, BIG};

game_size_t convert_user_input_to_game_size_t(char *user_input) {
  size_t i;
  char local_buffer[255];
  // TO-DO validate user's input length

  strcpy(local_buffer, user_input);
  lower_str(local_buffer);

  for (i = 0; i < sizeof(valid_user_values) / sizeof(char *); i++) {

    if (!(are_strs_eq((char *)valid_user_values[i], local_buffer)))
      continue;

    return user_values_game_size_map[i];
  }

  return -1;
}

game_config_ptr create_size_cli(game_config_ptr game_config, char *value) {
  game_size_t game_size;

  if (!value) {
    // set ERRNO
    // log message
    return NULL;
  }

  game_size = convert_user_input_to_game_size_t(value);

  if (game_size < 0) {
    // set ERRNO
    // log message
    return NULL;
  }

  set_game_config_size(game_config, game_size);

  return game_config;
}
