#ifndef _p_create_game_config_utils_cli_h
#define _p_create_game_config_utils_cli_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include <stddef.h>

/*******************************************************************************
 *    API
 ******************************************************************************/
char *sanitize_user_input(char *user_input, size_t buffer_size,
                          char buffer[buffer_size]);

#endif
