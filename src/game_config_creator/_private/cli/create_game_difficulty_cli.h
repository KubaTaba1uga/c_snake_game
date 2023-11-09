#ifndef _p_create_game_difficulty_cli_h
#define _p_create_game_difficulty_cli_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include "../../../game_config/game_config.h"

/*******************************************************************************
 *    API
 ******************************************************************************/
game_config_ptr create_game_difficulty_cli(game_config_ptr game_config,
                                           char *value);

#endif
