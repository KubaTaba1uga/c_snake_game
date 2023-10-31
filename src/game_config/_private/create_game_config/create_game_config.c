#include "create_game_config.h"
#include "cli/_p_create_game_config_cli.h"

game_config_ptr create_game_config(int argc, char *argv[]) {
  return create_game_config_from_cli(argc, argv);
}
