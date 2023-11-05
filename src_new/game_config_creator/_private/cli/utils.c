#include <stddef.h>
#include <string.h>

#include "../../../utils/str_utils.h"

char *sanitize_user_input(char *user_input, size_t buffer_size,
                          char buffer[buffer_size]) {
  void *no_err;

  no_err = strncpy(buffer, user_input, buffer_size - 1);
  if (!no_err) {
    goto ERROR;
  }

  // Make sure new string is NULL terminated
  buffer[buffer_size - 1] = 0;

  trim_trailing_whitespaces_str(buffer);

  lower_str(buffer);

  return buffer;

ERROR:
  return NULL;
}
