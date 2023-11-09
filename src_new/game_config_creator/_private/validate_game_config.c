#include "../../game_config/game_config.h"
#include "../../utils/logging_utils.h"
#include <stdbool.h>
#include <stdlib.h>

static void _log_error(char *msg);
static game_config_ptr
_validate_game_config_auto(game_config_ptr default_game_config,
                           game_config_ptr org_game_config);

const char *file_id = "validate_game_config";

game_config_ptr validate_game_config_auto(int _, char *__[],
                                          game_config_ptr game_config) {
  game_config_ptr default_game_config;
  void *game_config_is_valid;

  default_game_config = create_game_config();

  if (!default_game_config) {
    _log_error("Unable to allocate memory for default game config");

    return NULL;
  }

  game_config_is_valid =
      _validate_game_config_auto(default_game_config, game_config);

  destroy_game_config(default_game_config);

  if (!game_config_is_valid) {
    _log_error("Game config validation failed");

    return NULL;
  }

  return game_config;
}

game_config_ptr _validate_game_config_auto(game_config_ptr default_game_config,
                                           game_config_ptr org_game_config) {

  if (get_game_config_difficulty(default_game_config) ==
      get_game_config_difficulty(org_game_config)) {

    _log_error("Unable to find value for `game difficulty`");

    goto ERROR;
  }

  if (get_game_config_size(default_game_config) ==
      get_game_config_size(org_game_config)) {

    _log_error("Unable to find value for `game size`");

    goto ERROR;
  }

  if (get_game_config_users_types(default_game_config) ==
      get_game_config_users_types(org_game_config)) {

    _log_error("Unable to find value for `users`");

    goto ERROR;
  }

  return org_game_config;

ERROR:
  return NULL;
}

void _log_error(char *msg) { log_error((char *)file_id, msg); }
