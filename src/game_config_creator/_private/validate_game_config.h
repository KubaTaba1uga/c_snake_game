#ifndef _game_config_creator_validation_h
#define _game_config_creator_validation_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include "../../game_config/game_config.h"

/*******************************************************************************
 *    API
 ******************************************************************************/
game_config_ptr validate_game_config_auto(int _, char *__[],
                                          game_config_ptr game_config);

#endif
