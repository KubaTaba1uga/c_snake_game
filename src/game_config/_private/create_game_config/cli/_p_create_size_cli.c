#include "_p_game_config.h"
#include "game_size.h"

game_config_ptr create_size_cli(game_config_ptr game_config, char *value) {
  if (!value) {
    // set ERRNO
    // log message
    return NULL;
  }
  game_size_t game_size = SMALL;

  set_game_config_size(game_config, game_size);

  return game_config;
}
