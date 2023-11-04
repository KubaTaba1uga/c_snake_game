#ifndef _game_config_test_utils_h
#define _game_config_test_utils_h

#include "game_config/game_config.h"

extern game_config_ptr game_config_mock;

void create_game_config_mock(void);
void destroy_game_config_mock(void);

#endif
