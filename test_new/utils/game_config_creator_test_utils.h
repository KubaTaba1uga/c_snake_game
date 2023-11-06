#ifndef _game_config_creator_test_utils_h
#define _game_config_creator_test_utils_h

#include "game_config/user_type.h"

extern user_type_t *users_types_mock;

void create_users_types_mock(void);

void destroy_users_types_mock(void);

#endif
