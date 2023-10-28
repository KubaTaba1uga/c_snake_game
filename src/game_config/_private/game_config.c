#include "../game_config.h"
#include "../../interfaces/std_lib_interface.h"
#include "../../user/user_type.h"
#include "../game_difficulty.h"
#include "../game_size.h"
#include "../game_type.h"
#include "_p_game_config.h"

#include "stddef.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/

struct game_config {
  game_type_t type;

  game_difficulty_t difficulty;

  game_size_t size;

  size_t users_amount;

  user_type_t *users_types;
};

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
game_config_ptr create_game_config(void) {
  game_config_ptr local_game_config;

  local_game_config = app_malloc(sizeof(struct game_config));

  if (!local_game_config)
    // TO-DO set errno to OOM error
    return NULL;

  return local_game_config;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/

void destroy_game_config(game_config_ptr game_config) { app_free(game_config); }

game_type_t get_game_config_type(game_config_ptr game_config) {
  return game_config->type;
}

void set_game_config_type(game_config_ptr game_config, game_type_t game_type) {
  game_config->type = game_type;
}

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
