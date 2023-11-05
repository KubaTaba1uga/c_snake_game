#ifndef _str_utils_h
#define _str_utils_h

#include <stdbool.h>
#include <stddef.h>

void lower_str(char *str);

bool are_strs_eq(char *src, char *target);

void cut_str(char *str, size_t i);

void trim_trailing_whitespaces_str(char *str);

#endif
