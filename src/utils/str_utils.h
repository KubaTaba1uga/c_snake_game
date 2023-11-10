#ifndef _str_utils_h
#define _str_utils_h

#include <stdbool.h>
#include <stddef.h>

void lower_str(char *str);

bool are_strs_eq(char *src, char *target);

void cut_str(char *str, size_t i);

void remove_spaces(char *str);

#endif
