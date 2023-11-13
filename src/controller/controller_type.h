#ifndef _controller_type_h
#define _controller_type_h

/*******************************************************************************
 *   API
 ******************************************************************************/
typedef enum {
  CONTROLLER_LOCAL = 0,
  CONTROLLER_DUMMY,

  CONTROLLER_TYPE_ENUM_LEN,
} controller_type_t;

/* const char *str_controller_type(controller_type_t controller_type); */

#endif
