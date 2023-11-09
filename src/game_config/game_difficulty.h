#ifndef _game_difficulty_h
#define _game_difficulty_h

/*******************************************************************************
 *   API
 ******************************************************************************/
typedef enum {
  EASY = 0,
  MEDIUM,
  HARD,

  GAME_DIFFICULTY_ENUM_LEN,
} game_difficulty_t;

const char *str_game_difficulty(game_difficulty_t game_difficulty);

#endif
