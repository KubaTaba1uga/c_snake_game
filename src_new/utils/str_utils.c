// C standard library
#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#include "str_utils.h"

void lower_str(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

bool are_strs_eq(char *src, char *target) { return (strcmp(src, target) == 0); }

void cut_str(char *str, size_t i) { str[i] = 0; }

void trim_trailing_whitespaces_str(char *str) {
  int i = strlen(str) - 1;
  while (i >= 0) {
    if (str[i] == ' ' || str[i] == '\t')
      i--;
    else
      break;
  }
  str[i + 1] = '\0';
}
