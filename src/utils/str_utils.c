// C standard library
#include <ctype.h>

char *lower_str(char *str) {

  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }

  return str;
}
