#ifndef _str_utils_h
#define _str_utils_h

#include <stdbool.h>
#include <stddef.h>

char *lower_str(char *str);

bool are_strs_eq(char *src, char *target);
char *cut_str(char *str, size_t i);
#endif
