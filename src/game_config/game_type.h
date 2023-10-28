/*
 * Game type selected by the User.
 */
#ifndef _game_type_h
#define _game_type_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef enum {
  LOCAL = 0,
  LAN,

  /* Enum assigns values automatically by incrementing
   *   the first value. `GAME_TYPE_ENUM_LEN` stands for number
   *   of elements in enum (aka `length`).
   */
  GAME_TYPE_ENUM_LEN,
} game_type_t;

/* const char *str_game_type(game_type_t game_type); */

#endif
