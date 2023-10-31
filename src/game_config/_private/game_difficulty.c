#include "../game_difficulty.h"

const char *game_difficulty_s[] = {"easy", "medium", "hard"};

const char default_difficulty_text[] = "unrecognized";

const char *str_game_difficulty(game_difficulty_t game_difficulty) {
  if (game_difficulty < 0 ||
      game_difficulty > sizeof(game_difficulty_s) / sizeof(char *))
    return default_difficulty_text;

  return game_difficulty_s[game_difficulty];
}
