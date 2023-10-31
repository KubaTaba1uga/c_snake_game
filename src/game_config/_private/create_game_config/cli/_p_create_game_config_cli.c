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
#include "../../../../interfaces/std_lib_interface.h"
#include "../../../../user/user_type.h"
#include "../../../../utils/logging_utils.h"
#include "../../../game_difficulty.h"
#include "../../../game_size.h"
#include "../../../game_type.h"
#include "../../_p_game_config.h"
#include "_p_create_difficulty_cli.h"
#include "_p_create_game_config_cli.h"
#include "_p_create_size_cli.h"

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
/* inline int get_option_i(char c); */
inline game_config_ptr (*get_creation_function(int getopt_option_i))(
    game_config_ptr game_config, char *value);

/* inline void init_getopt_fmt(void); */

inline game_config_ptr create_game_type(game_config_ptr game_conifg,
                                        char *value);

/*******************************************************************************
 *    DATA
 ******************************************************************************/
struct option getopt_options[] = {{"size", required_argument, 0, 's'},
                                  {"difficulty", required_argument, 0, 'd'},
                                  {"game_type", required_argument, 0, 'g'},
                                  {"add", no_argument, 0, 'a'},
                                  {0, 0, 0, 0}};

game_config_ptr (*const getopt_options_creation_functions_map[])(
    game_config_ptr game_conifg, char *value) = {
    create_size_cli,
    create_difficulty_cli,
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

  optind = 1;
  printf("start optind: %i\n", optind);

  game_config = create_game_config();

  if (!game_config) {
    // TO-DO set errno to OOM
    // TO-DO log messgae
    return NULL;
  }

  /* init_getopt_fmt(); */

  while (true) {
    int x = 0;

    getopt_flag = getopt_long(argc, argv, "s:d:", getopt_options, &x);

    printf("c: %c\n", getopt_flag);
    printf("optind: %i\n", optind);

    option_i = 0;

    if (option_i < 0) {
      // TO-DO set errno to unknown option
      // TO-DO log messgae
      // TO-DO print to stdout
      return NULL;
    }

    /* Detect the end of the options. */
    if (getopt_flag == -1)
      break;

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
/* int get_option_i(char c) { */
/*   size_t i; */
/*   for (i = 0; i < sizeof(getopt_options) / sizeof(struct option); i++) { */
/*     if (getopt_options[i].val == c) */
/*       return i; */
/*   } */
/*   return -1; */
/* } */

game_config_ptr (*get_creation_function(int getopt_option_i))(
    game_config_ptr game_config, char *value) {
  // TO-DO Validate input
  return getopt_options_creation_functions_map[getopt_option_i];
}

/* void init_getopt_fmt(void) { */
/*   const char local_fmt[] = {getopt_options[0].val, ':',
 * getopt_options[1].val, */
/*                             ':', */
/*                             // NULL ending a string. Do not remove. */
/*                             0}; */
/*   size_t i; */

/*   for (i = 0; i < sizeof(local_fmt) / sizeof(char); i++) { */
/*     getopt_fmt[i] = local_fmt[i]; */
/*   } */
/* } */

game_config_ptr create_game_type(game_config_ptr game_conifg, char *value) {
  set_game_config_type(game_conifg, LOCAL);

  return game_conifg;
}
