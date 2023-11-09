/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// App
#include "../game_difficulty.h"

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static const char *const GAME_DIFFICULTY_STRINGS[] = {
    // 0
    "Easy",

    // 1
    "Medium",

    // 2
    "Hard",

};

static const size_t GAME_DIFFICULTY_STRINGS_LEN =
    sizeof(GAME_DIFFICULTY_STRINGS) / sizeof(char *);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

const char *str_game_difficulty(game_difficulty_t game_difficulty) {
  if ( // Upper bound
      (game_difficulty >= GAME_DIFFICULTY_ENUM_LEN) ||
      (game_difficulty >= GAME_DIFFICULTY_STRINGS_LEN) ||
      // Lower bound
      (game_difficulty < 0))
    return NULL;

  return GAME_DIFFICULTY_STRINGS[game_difficulty];
}
