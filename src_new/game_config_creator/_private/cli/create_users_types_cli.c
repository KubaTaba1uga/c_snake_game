/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// App
#include "../../../game_config/game_config.h"
#include "../../../game_config/user_type.h"
#include "../../../interfaces/std_lib_interface.h"
#include "../../../proj_config/constant.h"
#include "../../../proj_config/error.h"
#include "../../../utils/logging_utils.h"
#include "create_user_type_cli.h"
#include "utils.h"

/*******************************************************************************
 *    DATA
 ******************************************************************************/
static const char file_id[] = "create_users_types_cli";
static const size_t max_users_amount = 100;

/*******************************************************************************
 *    PRIVATE DECLARATIONS
 ******************************************************************************/
inline game_config_ptr _create_users_types_cli(game_config_ptr game_config,
                                               char *value);
inline user_type_t *create_users_types(void);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
game_config_ptr create_users_types_cli(game_config_ptr game_config,
                                       char *value) {
  game_config_ptr local_game_config;

  errno = 0;

  local_game_config = _create_users_types_cli(game_config, value);

  if (!local_game_config) {
    switch (errno) {

    case ERROR_OOM:
      log_error((char *)file_id, "Unable to allocate memory for users types.",
                value);
      break;

    case ERROR_INVALID_USER_INPUT:
      log_error((char *)file_id, "Invalid user input `%s`", value);
      break;

    case ERROR_TOO_MANY_USERS:
      log_error((char *)file_id, "Maximum users amount is %i",
                max_users_amount);
      break;

    default:
      log_error((char *)file_id, "Unknown errno value %i", errno);
    }
  }

  return local_game_config;
}

/*******************************************************************************
 *    PRIVATE API
 ******************************************************************************/
game_config_ptr _create_users_types_cli(game_config_ptr game_config,
                                        char *value) {
  user_type_t *users_types, user_type;
  size_t users_number;

  if (!value) {
    errno = ERROR_INVALID_USER_INPUT;
    goto ERROR;
  }

  user_type = convert_user_input_to_user_type_t(value);

  if (user_type == ENUM_INVALID) {
    goto ERROR;
  }

  users_types = get_game_config_users_types(game_config);

  if (!users_types) {
    users_types = create_users_types();
    if (!users_types) {
      goto ERROR;
    }
  }

  users_number = get_game_config_users_amount(game_config);

  /* printf("Users amount: %lu\n\n\n", users_number); */

  /* if (users_number > max_users_amount) { */
  /*   app_free(users_types); */
  /*   errno = ERROR_TOO_MANY_USERS; */
  /*   goto ERROR; */
  /* } */
  printf("New value: `%i`\n", user_type);
  printf("Before assignment Last value: `%i`\n", users_types[users_number]);
  /* printf("Before assignment New value: `%i`\n", user_type); */

  users_types[users_number] = user_type;

  /* printf("User type private: %i\n", users_types[users_number]); */

  users_number++;

  set_game_config_users_types(game_config, users_number, users_types);

  printf("After assignment Last value: `%i`\n\n",
         users_types[users_number - 1]);

  return game_config;

ERROR:
  /* set_game_config_users_types(game_config, 0, NULL); */
  return NULL;
}

user_type_t *create_users_types(void) {
  user_type_t *local_users_types;

  local_users_types = malloc(max_users_amount * sizeof(user_type_t));

  if (!local_users_types) {
    errno = ERROR_OOM;
    return NULL;
  }

  return local_users_types;
}
