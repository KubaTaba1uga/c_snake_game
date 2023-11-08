#ifndef _game_config_test_utils_h
#define _game_config_test_utils_h

#include "game_config/game_config.h"
#include <stddef.h>

extern game_config_ptr game_config_mock;
extern size_t game_config_expect_size;

void create_game_config_mock(void);
void destroy_game_config_mock(void);

void TEST_ASSERT_GAME_DIFFICULTY(game_difficulty_t expected,
                                 game_difficulty_t recived);
void TEST_ASSERT_GAME_SIZE(game_size_t expected, game_size_t recived);
void TEST_ASSERT_GAME_TYPE(game_type_t expected, game_type_t recived);
void TEST_ASSERT_USER_TYPE(user_type_t expected, user_type_t recived);

#endif
