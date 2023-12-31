/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <errno.h>
#include <stddef.h>

// App
#include "../../interfaces/std_lib_interface.h"
#include "../../proj_config/constant.h"
#include "../../proj_config/error.h"
#include "../game_config.h"
#include "../game_difficulty.h"
#include "../game_size.h"
#include "../user_type.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
struct game_config {
  game_difficulty_t difficulty;

  game_size_t size;

  size_t users_amount;

  user_type_t *users_types;
};

/*******************************************************************************
 *    API
 ******************************************************************************/
game_config_ptr create_game_config(void) {
  game_config_ptr local_game_config;

  local_game_config = app_malloc(sizeof(struct game_config));

  if (!local_game_config) {
    errno = ERROR_OOM;
    goto ERROR;
  }

  local_game_config->difficulty = ENUM_INVALID;
  local_game_config->size = ENUM_INVALID;
  local_game_config->users_amount = 0;
  local_game_config->users_types = NULL;

  return local_game_config;

ERROR:
  return NULL;
}

void destroy_game_config(game_config_ptr game_config) { app_free(game_config); }

game_difficulty_t get_game_config_difficulty(game_config_ptr game_config) {
  return game_config->difficulty;
}

void set_game_config_difficulty(game_config_ptr game_config,
                                game_difficulty_t game_difficulty) {
  game_config->difficulty = game_difficulty;
}

game_size_t get_game_config_size(game_config_ptr game_config) {
  return game_config->size;
}

void set_game_config_size(game_config_ptr game_config, game_size_t game_size) {
  game_config->size = game_size;
}

size_t get_game_config_users_amount(game_config_ptr game_config) {
  return game_config->users_amount;
}

user_type_t *get_game_config_users_types(game_config_ptr game_config) {
  return game_config->users_types;
}

void set_game_config_users_types(game_config_ptr game_config,
                                 size_t users_amount,
                                 user_type_t users_types[users_amount]) {
  game_config->users_amount = users_amount;
  game_config->users_types = users_types;
}
