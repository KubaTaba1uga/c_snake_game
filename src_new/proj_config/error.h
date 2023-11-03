#ifndef _error_h
#define _error_h

/*******************************************************************************
 *    IMPORTS
 ******************************************************************************/
#include <stddef.h>

/*******************************************************************************
 *    PUBLIC API
 ******************************************************************************/
typedef enum {
  NO_ERROR = 0,
  ERROR_OOM,
  ERROR_NULL_POINTER,
  ERROR_GENERIC,

  /* Enum assigns values automatically by incrementing
   *   the first value. `ERROR_ENUM_LEN` stands for number
   *   of elements in enum (aka `length`).
   */
  ERROR_ENUM_LEN,
} error_t;

/* const char *str_error(error_t error); */

#endif
