/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// App
#include "../game_type.h"

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static const char *const GAME_TYPE_STRINGS[] = {
    // 0
    "Local",

    // 1
    "Server",

    // 2
    "Client",

};

static const size_t GAME_TYPE_STRINGS_LEN =
    sizeof(GAME_TYPE_STRINGS) / sizeof(char *);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

const char *str_game_type(game_type_t game_type) {
  if ( // Upper bound
      (game_type >= GAME_TYPE_ENUM_LEN) ||
      (game_type >= GAME_TYPE_STRINGS_LEN) ||
      // Lower bound
      (game_type < 0))
    return NULL;

  return GAME_TYPE_STRINGS[game_type];
}
