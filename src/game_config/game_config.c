#include "game_config.h"
#include "../user/user_type.h"
#include "game_difficulty.h"
#include "game_size.h"
#include "game_type.h"
#include "stddef.h"

/*******************************************************************************
 *    PRIVATE API DECLARATIONS
 ******************************************************************************/

struct game_config {
  game_type_t type;

  game_difficulty_t difficulty;

  game_size_t size;

  size_t players_amount;

  user_type_t users_types[];
};
