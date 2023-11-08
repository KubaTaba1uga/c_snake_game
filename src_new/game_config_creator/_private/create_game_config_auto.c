/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <errno.h>
#include <stddef.h>
#include <stdio.h>

// App
#include "../../game_config/game_config.h"
#include "../../interfaces/std_lib_interface.h"
#include "../../proj_config/error.h"
#include "../../utils/logging_utils.h"
#include "cli/create_game_config_cli.h"

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
static game_config_ptr _create_game_config_auto(int argc, char **argv,
                                                game_config_ptr game_config);

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char file_id[] = "create_game_config_auto";
static game_config_ptr (*const creation_functions[])(
    int argc, char **argv, game_config_ptr game_conifg) = {
    create_game_config_cli,
};
static const size_t creation_f_size =
    sizeof(creation_functions) / sizeof(void *);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

game_config_ptr create_game_config_auto(int argc, char *argv[]) {
  // TO-DO game config needs to be shared among creator functions

  game_config_ptr game_config;
  void *received;

  game_config = create_game_config();

  if (!game_config) {
    log_error((char *)file_id, "Unable to allocate memory for game config.");
    goto ERROR;
  }

  received = _create_game_config_auto(argc, argv, game_config);

  if (!received) {
    // Detailed error logs should be provided by creation function.
    app_free(game_config);
    errno = ERROR_GAME_CONFIG_CREATION_FAILURE;
    log_error((char *)file_id, "Game config creation failed");
    goto ERROR;
  }

  return game_config;

ERROR:
  return NULL;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
game_config_ptr _create_game_config_auto(int argc, char **argv,
                                         game_config_ptr game_config) {
  game_config_ptr (*creation_function)(int argc, char **argv,
                                       game_config_ptr game_config);
  size_t i, failure_counter;
  void *received;

  failure_counter = 0;

  for (i = 0; i < creation_f_size; i++) {
    creation_function = creation_functions[i];

    received = creation_function(argc, argv, game_config);

    if (!received)
      failure_counter++;
    else
      game_config = received;
  }

  if (failure_counter == creation_f_size) {
    return NULL;
  }

  return game_config;
}
