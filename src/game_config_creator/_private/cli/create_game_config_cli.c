/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <ctype.h>
#include <errno.h>
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
#include "../../../game_config/user_type.h"
#include "../../../interfaces/std_lib_interface.h"
#include "../../../proj_config/error.h"
#include "../../../utils/logging_utils.h"
#include "create_game_difficulty_cli.h"
#include "create_game_size_cli.h"
#include "create_users_types_cli.h"

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
static int get_option_i(char c);

static game_config_ptr (*get_creation_function(int getopt_option_i))(
    game_config_ptr game_config, char *value);

static void init_getopt_fmt(size_t n, struct option options[n]);

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char *file_id = "create_game_config_cli";

static struct option getopt_options[] = {
    {"size", required_argument, 0, 's'},
    {"difficulty", required_argument, 0, 'd'},
    {"user", required_argument, 0, 'u'},
    {0, 0, 0, 0}};

static game_config_ptr (*const getopt_options_creation_functions_map[])(
    game_config_ptr game_conifg, char *value) = {
    create_game_size_cli,
    create_game_difficulty_cli,
    create_users_types_cli,
    NULL,
};

static char getopt_fmt[255];

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

game_config_ptr create_game_config_cli(int argc, char *argv[],
                                       game_config_ptr game_config) {
  game_config_ptr (*creation_function)(game_config_ptr game_config,
                                       char *value);
  int option_i;
  char getopt_flag;

  // Optind reset is required so function can be
  //  executed multiple times. Without the reset
  //  getopt is not repeateble.
  optind = 1;

  init_getopt_fmt(sizeof(getopt_options) / sizeof(struct option),
                  getopt_options);

  while (true) {
    getopt_flag = getopt_long(argc, argv, getopt_fmt, getopt_options, NULL);

    /* Detect the end of the options. */
    if (getopt_flag == -1)
      break;

    option_i = get_option_i(getopt_flag);

    if (option_i < 0) {
      if (optopt)
        log_error((char *)file_id, "Cannot recognize option %c", optopt);
      else
        log_error((char *)file_id, "Cannot recognize option %s",
                  argv[optind - 1]);

      errno = ERROR_CLI_INVALID_OPTION;

      goto ERROR;
    }

    creation_function = get_creation_function(option_i);

    if (!creation_function) {
      errno = ERROR_GAME_CONFIG_CREATION_FAILURE;

      log_error((char *)file_id, "Cannot find creation function for %c",
                (char)getopt_flag);

      goto ERROR;
    }

    game_config = creation_function(game_config, optarg);

    if (!game_config) {
      // Creation function logs it's errors
      //  and sets it's errnos.
      goto ERROR;
    }
  }

  return game_config;

ERROR:
  return NULL;
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
