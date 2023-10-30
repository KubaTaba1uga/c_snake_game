/* #include "_p_create_game_config_from_cli.h" */
/* #include "../../../interfaces/std_lib_interface.h" */
/* #include "../../../user/user_type.h" */
/* #include "../../../utils/logging_utils.h" */
/* #include "../../game_type.h" */
/* #include "../_p_game_config.h" */
/* #include "game_difficulty.h" */
/* #include "user_type.h" */
/* #include <ctype.h> */
/* #include <getopt.h> */
/* #include <stdbool.h> */
/* #include <stddef.h> */
/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <string.h> */
/* #include <unistd.h> */

/* const char FLAGS[] = { */
/*     // Difficulty */
/*     'd', */
/*     // User Type */
/*     'u', */
/* }; */

/* char *lower_str(char *str) { */

/*   for (int i = 0; str[i]; i++) { */
/*     str[i] = tolower(str[i]); */
/*   } */

/*   return str; */
/* } */

/* inline game_config_ptr create_game_type(int argc, char *argv[], */
/*                                         game_config_ptr game_conifg); */
/* inline game_config_ptr create_difficulty(int argc, char *argv[], */
/*                                          game_config_ptr game_conifg); */
/* inline game_config_ptr create_size(int argc, char *argv[], */
/*                                    game_config_ptr game_conifg); */

/* game_config_ptr (*const creation_functions[])(int argc, char *argv[], */
/*                                               game_config_ptr game_conifg) =
 * { */
/*     create_game_type, create_difficulty, create_size}; */

/* game_config_ptr create_game_config_from_cli(int argc, char *argv[]) { */
/*   game_config_ptr game_config; */
/*   size_t i; */

/*   game_config = create_game_config(); */

/*   if (!game_config) { */
/*     // TO-DO set errno to OOM */
/*     // TO-DO log messgae */
/*     return NULL; */
/*   } */

/*   for (i = 0; i < sizeof(creation_functions) / sizeof(void *); i++) { */
/*     game_config = creation_functions[i](argc, argv, game_config); */

/*     if (!game_config) { */
/*       // TO-DO set errno to CONFIG CREATION ERROR */
/*       // TO-DO log message */
/*       return NULL; */
/*     } */
/*   } */

/*   return game_config; */
/* } */

/* game_config_ptr create_difficulty(int argc, char *argv[], */
/*                                   game_config_ptr game_config) { */
/*   const char *valid_user_values[] = {"easy", "medium", "hard"}; */
/*   const game_difficulty_t user_values_difficulty_map[] = {EASY, MEDIUM,
 * HARD}; */
/*   const char getopt_fmt[] = {FLAGS[0], ':'}; */

/*   game_difficulty_t game_config_difficulty; */
/*   char *difficulty_user_value; */
/*   char *user_value_cp; */
/*   int flag; */
/*   size_t i; */

/*   difficulty_user_value = NULL; */

/*   while ((flag = getopt(argc, argv, getopt_fmt)) != -1) { */

/*     if (flag == (int)FLAGS[0]) { */
/*       difficulty_user_value = optarg; */
/*     } */
/*   } */

/*   // Set default */
/*   if (!difficulty_user_value) { */
/*     set_game_config_difficulty(game_config, EASY); */

/*     return game_config; */
/*   } */

/*   // Lowerize */
/*   user_value_cp = malloc(sizeof(char) * (strlen(difficulty_user_value) + 1));
 */

/*   if (!user_value_cp) { */
/*     // TO-DO set errno to OOM */
/*     // TO-DO log error */
/*     return NULL; */
/*   } */

/*   strncpy(user_value_cp, difficulty_user_value, */
/*           strlen(difficulty_user_value) + 1); */

/*   difficulty_user_value = lower_str(user_value_cp); */

/*   // Map user input to game_config_type_t */
/*   game_config_difficulty = -1; */

/*   for (i = 0; */
/*        i < sizeof(user_values_difficulty_map) / sizeof(game_difficulty_t); */
/*        i++) { */

/*     if (!strcmp(valid_user_values[i], difficulty_user_value)) { */
/*       game_config_difficulty = user_values_difficulty_map[i]; */
/*     } */
/*   } */

/*   if (game_config_difficulty == -1) { */
/*     // TO-DO set errno to CGC NO DIFFICULTY VALUE */
/*     // TO-DO log error */
/*     puts("-1"); */
/*     return NULL; */
/*   } */

/*   set_game_config_difficulty(game_config, game_config_difficulty); */

/*   app_free(difficulty_user_value); */

/*   return game_config; */
/* } */

/* game_config_ptr create_game_type(int argc, char *argv[], */
/*                                  game_config_ptr game_conifg) { */
/*   /\* bool user_is *\/ */

/*   return game_conifg; */
/* } */

/* game_config_ptr create_size(int argc, char *argv[], */
/*                             game_config_ptr game_conifg) { */
/*   return game_conifg; */
/* } */
