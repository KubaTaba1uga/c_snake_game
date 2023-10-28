/*
 * Game size selected by the User. Smaller size means less
 * tiles for snakes to move on.
 */
#ifndef _game_size_h
#define _game_size_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef enum {
  SMALL = 0,
  AVARAGE,
  BIG,

  /* Enum assigns values automatically by incrementing
   *   the first value. `GAME_SIZE_ENUM_LEN` stands for number
   *   of elements in enum (aka `length`).
   */
  GAME_SIZE_ENUM_LEN,
} game_size_t;

/* const char *str_game_size(game_size_t game_size); */

#endif
