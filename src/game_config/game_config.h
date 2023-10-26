/*
 * Game configuration provided by the User.
 */
#ifndef _game_config_h
#define _game_config_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include "../error.h"

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef struct game_config *game_config_ptr;

error_t create_game_config(game_config_ptr *game_config);
void destroy_game_config(game_config_ptr game_config);

#endif
