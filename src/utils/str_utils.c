// C standard library
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "str_utils.h"

char *lower_str(char *str) {

  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }

  return str;
}

bool are_strs_eq(char *src, char *target) { return (strcmp(src, target) == 0); }

char *cut_str(char *str, size_t i) {
  str[i] = 0;
  return str;
}
