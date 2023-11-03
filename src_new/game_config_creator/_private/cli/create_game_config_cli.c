/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// App
#include "../../../game_config/game_config.h"
#include "../../../game_config/game_difficulty.h"
#include "../../../game_config/game_size.h"
#include "../../../game_config/game_type.h"
#include "../../../game_config/user_type.h"
#include "../../../interfaces/std_lib_interface.h"
#include "../../../utils/logging_utils.h"
#include "create_game_difficulty_cli.h"
#include "create_game_size_cli.h"

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
inline int get_option_i(char c);

inline game_config_ptr (*get_creation_function(int getopt_option_i))(
    game_config_ptr game_config, char *value);

inline void init_getopt_fmt(size_t n, struct option options[n]);

inline game_config_ptr create_game_type(game_config_ptr game_conifg,
                                        char *value);

/*******************************************************************************
 *    DATA
 ******************************************************************************/
struct option getopt_options[] = {{"size", required_argument, 0, 's'},
                                  {"difficulty", required_argument, 0, 'd'},
                                  {"game_type", required_argument, 0, 'g'},
                                  {0, 0, 0, 0}};

game_config_ptr (*const getopt_options_creation_functions_map[])(
    game_config_ptr game_conifg, char *value) = {
    create_game_size_cli,
    create_game_difficulty_cli,
    create_game_type,
    NULL,
};

char getopt_fmt[255];

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

game_config_ptr create_game_config_from_cli(int argc, char *argv[]) {
  game_config_ptr (*creation_function)(game_config_ptr game_config,
                                       char *value);
  game_config_ptr game_config;
  int getopt_flag, option_i;

  // Optind reset is required so function can be
  //  executed multiple times. Without the reset
  //  getopt is not repeateble.
  optind = 1;

  game_config = create_game_config();

  if (!game_config) {
    // TO-DO set errno to OOM
    // TO-DO log messgae
    return NULL;
  }

  init_getopt_fmt(sizeof(getopt_options) / sizeof(struct option),
                  getopt_options);

  while (true) {
    getopt_flag = getopt_long(argc, argv, getopt_fmt, getopt_options, NULL);

    /* Detect the end of the options. */
    if (getopt_flag == -1)
      break;

    option_i = get_option_i(getopt_flag);

    if (option_i < 0) {
      // TO-DO set errno to unknown option
      // TO-DO log messgae
      // TO-DO print to stdout
      return NULL;
    }

    creation_function = get_creation_function(option_i);

    if (!creation_function) {
      // TO-DO set errno to unknown option
      // TO-DO log messgae
      // TO-DO print to stdout
      return NULL;
    }

    game_config = creation_function(game_config, optarg);
  }

  return game_config;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
int get_option_i(char c) {
  size_t i;
  for (i = 0; i < sizeof(getopt_options) / sizeof(struct option); i++) {
    if (getopt_options[i].val == c)
      return i;
  }
  return -1;
}

game_config_ptr (*get_creation_function(int getopt_option_i))(
    game_config_ptr game_config, char *value) {
  // TO-DO Validate input
  return getopt_options_creation_functions_map[getopt_option_i];
}

void init_getopt_fmt(size_t n, struct option options[n]) {
  size_t i, local_i = 0;

  for (i = 0; i < n; i++) {
    getopt_fmt[local_i++] = options[i].val;

    switch (options[i].has_arg) {
    case required_argument:
      getopt_fmt[local_i++] = ':';
      break;
    case optional_argument:
      getopt_fmt[local_i++] = ':';
      getopt_fmt[local_i++] = ':';
      break;
    default:;
    }
  }
}

game_config_ptr create_game_type(game_config_ptr game_conifg, char *value) {
  set_game_config_type(game_conifg, LOCAL);

  return game_conifg;
}
