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
  LAN_SERVER,
  LAN_CLIENT,

  USER_TYPE_ENUM_LEN,
} user_type_t;

const char *str_user_type(user_type_t user_type);

#endif
