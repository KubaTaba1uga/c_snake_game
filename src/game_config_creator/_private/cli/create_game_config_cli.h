#ifndef _p_create_game_config_cli_h
#define _p_create_game_config_cli_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include "../../../game_config/game_config.h"

/*******************************************************************************
 *    API
 ******************************************************************************/
game_config_ptr create_game_config_cli(int argc, char *argv[],
                                       game_config_ptr game_config);

#endif
