#ifndef MY_GREP_UTILS_H
#define MY_GREP_UTILS_H

#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "my_grep_types.h"

int is_duplicate(const char *str0, const char *str1, int ignore_case);
int redouble_str(char **str, size_t *max_len);
void remove_newline(char *str);
int count_elements(s_str_el *element);

#endif
