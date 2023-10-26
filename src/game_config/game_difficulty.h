/*
 * Game difficulty level selected by the User. Easier game means smaller
 * ammount of points required to win a level.
 */
#ifndef _game_difficulty_h
#define _game_difficulty_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef enum {
  EASY = 0,
  MEDIUM,
  HARD,

  /* Enum assigns values automatically by incrementing
   *   the first value. `GAME_DIFFICULTY_ENUM_LEN` stands for number
   *   of elements in enum (aka `length`).
   */
  GAME_DIFFICULTY_ENUM_LEN,
} game_difficulty_t;

const char *str_game_difficulty(game_difficulty_t game_difficulty);

#endif
