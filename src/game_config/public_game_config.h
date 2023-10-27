/*
 * Game configuration provided by the User. This class should
 *  be imported outside of the game_config's module context.
 *  Setting values for game's config, is not allowed. To set up
 *  game's config, run cli's args > game's config converter.
 */
#ifndef _private_game_config_h
#define _private_game_config_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include <stddef.h>

#include "../error.h"
#include "../user/user_type.h"
#include "game_difficulty.h"
#include "game_size.h"
#include "game_type.h"

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef struct game_config *game_config_ptr;

error_t create_game_config(game_config_ptr *game_config);
void destroy_game_config(game_config_ptr game_config);

game_type_t get_game_config_type(game_config_ptr game_config);

game_difficulty_t get_game_config_difficulty(game_config_ptr game_config);

game_size_t get_game_config_size(game_config_ptr game_config);

size_t get_game_config_users_amount(game_config_ptr game_config);
user_type_t *get_game_config_users_types(game_config_ptr game_config);

#endif
