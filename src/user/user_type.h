/*
 * User type distinguish how the game will process player interactions.
 * Simple PC - controll snake without any human interactions. Pretty dumb.
 * Human - controll snake by interacting with the keyboard, on computer where
 * game is being played. Server - controll snake by receiving moves from another
 * computer.
 * Client - controll snake by sending moves to another computer.
 */
#ifndef _user_type_h
#define _user_type_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef enum {
  HUMAN = 0,
  SIMPLE_PC,

  /* Enum assigns values automatically by incrementing
   *   the first value. `GAME_TYPE_ENUM_LEN` stands for number
   *   of elements in enum (aka `length`).
   */
  USER_TYPE_ENUM_LEN,
} user_type_t;

const char *str_user_type(user_type_t user_type);

#endif
