/*
 * Game configuration provided by the User. This class shouldn't
 *  be imported outside of the game_config's module context.
 *  Setting values for game's config, is allowed only internally.
 */
#ifndef _p_game_config_h
#define _p_game_config_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include <stddef.h>

#include "../../user/user_type.h"
#include "../game_config.h"
#include "../game_difficulty.h"
#include "../game_size.h"
#include "../game_type.h"

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
game_config_ptr create_game_config(void);
void destroy_game_config(game_config_ptr game_config);

void set_game_config_type(game_config_ptr game_config, game_type_t game_type);
void set_game_config_difficulty(game_config_ptr game_config,
                                game_difficulty_t game_difficulty);
void set_game_config_size(game_config_ptr game_config, game_size_t game_size);
void set_game_config_users_types(game_config_ptr game_config,
                                 size_t users_amount,
                                 user_type_t users_types[users_amount]);
#endif
