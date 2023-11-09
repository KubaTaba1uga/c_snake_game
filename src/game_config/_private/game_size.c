/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// App
#include "../game_size.h"

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static const char *const GAME_SIZE_STRINGS[] = {
    // 0
    "Small",

    // 1
    "Avarage",

    // 2
    "Big",

};

static const size_t GAME_SIZE_STRINGS_LEN =
    sizeof(GAME_SIZE_STRINGS) / sizeof(char *);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

const char *str_game_size(game_size_t game_size) {
  if ( // Upper bound
      (game_size >= GAME_SIZE_ENUM_LEN) ||
      (game_size >= GAME_SIZE_STRINGS_LEN) ||
      // Lower bound
      (game_size < 0))
    return NULL;

  return GAME_SIZE_STRINGS[game_size];
}
