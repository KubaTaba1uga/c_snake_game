#include "game_config_creator/game_config_creator.h"
#include "utils/logging_utils.h"

void set_up(void) { init_loggers(); }

void tear_down(void) { destroy_loggers(); }

int main(int argc, char *argv[]) {
  set_up();

  create_game_config_auto(argc, argv);

  tear_down();
}
