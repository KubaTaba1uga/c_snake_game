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

void remove_spaces(char* s) {
  char* tmp = s;
  
  while (*tmp != 0) {
    while (*tmp == ' ') {
      tmp++;
    }

    *s++ = *tmp++;    
  }
  
}
