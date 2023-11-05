#include <stddef.h>
#include <string.h>

#include "../../../utils/str_utils.h"

char *sanitize_user_input(char *user_input, size_t buffer_size,
                          char buffer[buffer_size]) {
  void *no_err;

  no_err = strncpy(buffer, user_input, buffer_size);
  if (!no_err) {
    goto ERROR;
  }

  remove_spaces(buffer);

  cut_str(buffer, buffer_size - 1);
  
  lower_str(buffer);

  return buffer;

ERROR:
  return NULL;
}
