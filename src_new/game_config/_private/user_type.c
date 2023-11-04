/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
// C standard library
#include <stddef.h>

// App
#include "../user_type.h"

/*******************************************************************************
 *    PRIVATE DATA
 ******************************************************************************/
static const char *const USER_TYPE_STRINGS[] = {
    // 0
    "Human",

    // 1
    "EasyPc",

    // 2
    "LanServer",

    // 3
    "LanClient",
};

static const size_t USER_TYPE_STRINGS_LEN =
    sizeof(USER_TYPE_STRINGS) / sizeof(char *);

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/

const char *str_user_type(user_type_t user_type) {
  if ( // Upper bound
      (user_type >= USER_TYPE_ENUM_LEN) ||
      (user_type >= USER_TYPE_STRINGS_LEN) ||
      // Lower bound
      (user_type < 0))
    return NULL;

  return USER_TYPE_STRINGS[user_type];
}
