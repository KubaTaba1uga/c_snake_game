#ifndef _game_config_h
#define _game_config_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// App
#include "game_difficulty.h"
#include "game_size.h"
#include "user_type.h"

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef struct game_config *game_config_ptr;

game_config_ptr create_game_config(void);
void destroy_game_config(game_config_ptr game_config);

game_difficulty_t get_game_config_difficulty(game_config_ptr game_config);
void set_game_config_difficulty(game_config_ptr game_config,
                                game_difficulty_t game_difficulty);

game_size_t get_game_config_size(game_config_ptr game_config);
void set_game_config_size(game_config_ptr game_config, game_size_t game_size);

size_t get_game_config_users_amount(game_config_ptr game_config);
user_type_t *get_game_config_users_types(game_config_ptr game_config);

void set_game_config_users_types(game_config_ptr game_config,
                                 size_t users_amount,
                                 user_type_t users_types[users_amount]);

#endif
