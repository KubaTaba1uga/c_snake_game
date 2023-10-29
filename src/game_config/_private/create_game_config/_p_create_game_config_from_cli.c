#include "_p_create_game_config_from_cli.h"
#include "../_p_game_config.h"
#include "game_config.h"
#include <stddef.h>

inline game_config_ptr create_game_type(int argc, char *argv[],
                                        game_config_ptr game_conifg);
inline game_config_ptr create_difficulty(int argc, char *argv[],
                                         game_config_ptr game_conifg);
inline game_config_ptr create_size(int argc, char *argv[],
                                   game_config_ptr game_conifg);

game_config_ptr (*const creation_functions[])(int argc, char *argv[],
                                              game_config_ptr game_conifg) = {
    create_game_type, create_difficulty, create_size};

game_config_ptr create_game_config_from_cli(int argc, char *argv[]) {
  game_config_ptr game_config;
  size_t i;

  game_config = create_game_config();

  if (!game_config) {
    // TO-DO set errno to OOM
    // TO-DO log messgae
    return NULL;
  }

  for (i = 0; i < sizeof(creation_functions) / sizeof(void *); i++) {
    game_config = creation_functions[i](argc, argv, game_config);

    if (!game_config) {
      // TO-DO set errno to CONFIG CREATION ERROR
      // TO-DO log message
      return NULL;
    }
  }

  return game_config;
}

game_config_ptr create_game_type(int argc, char *argv[],
                                 game_config_ptr game_conifg) {
  return game_conifg;
}

game_config_ptr create_difficulty(int argc, char *argv[],
                                  game_config_ptr game_conifg) {
  return game_conifg;
}

game_config_ptr create_size(int argc, char *argv[],
                            game_config_ptr game_conifg) {
  return game_conifg;
}
