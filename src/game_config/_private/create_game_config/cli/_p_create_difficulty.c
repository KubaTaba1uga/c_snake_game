// C standard library
#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../../../../interfaces/std_lib_interface.h"
#include "../../../../user/user_type.h"
#include "../../../../utils/logging_utils.h"
#include "../../../../utils/str_utils.h"
#include "../../../game_type.h"
#include "../../_p_game_config.h"
#include "../_p_create_game_config_from_cli.h"
#include "../game_difficulty.h"
#include "../user_type.h"

const char *valid_user_values[] = {"easy", "medium", "hard"};
const game_difficulty_t user_values_difficulty_map[] = {EASY, MEDIUM, HARD};

game_difficulty_t create_difficulty(char *user_value) {

  game_difficulty_t user_difficulty;
  char *user_value_cp;
  size_t i;

  if (!user_value) {
    goto DEFAULT;
  }

  // Lowerize
  user_value_cp = malloc(sizeof(char) * (strlen(user_value) + 1));

  if (!user_value_cp) {
    // TO-DO set errno to OOM
    // TO-DO log error
    goto ERROR;
  }

  strncpy(user_value_cp, user_value, strlen(user_value) + 1);

  user_value = lower_str(user_value_cp);

  // Map user input to game_config_type_t
  user_difficulty = -1;

  for (i = 0;
       i < sizeof(user_values_difficulty_map) / sizeof(game_difficulty_t);
       i++) {

    if (!strcmp(valid_user_values[i], user_value)) {
      user_difficulty = user_values_difficulty_map[i];
    }
  }

  if (user_difficulty == -1) {
    // TO-DO set errno to CGC NO DIFFICULTY VALUE
    // TO-DO log error
    goto ERROR;
  }

  app_free(user_value);

  return user_difficulty;

ERROR:
  return -1;

DEFAULT:
  return EASY;
}
