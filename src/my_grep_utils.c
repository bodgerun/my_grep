#include "my_grep_utils.h"

int is_duplicate(const char *str0, const char *str1, int ignore_case) {
  int res;

  if (ignore_case) {
    res = !strcasecmp(str0, str1);
  } else {
    res = !strcmp(str0, str1);
  }

  return res;
}

int redouble_str(char **str, size_t *max_len) {
  int res_code = 0;

  *max_len *= 2;
  char *tmp = realloc(*str, *max_len * sizeof(*tmp));

  if (tmp) {
    *str = tmp;
  } else {
    res_code = -1;
  }

  return res_code;
}

void remove_newline(char *str) {
  for (int stop = 0; *str && !stop; str++) {
    if (*str == '\n') {
      *str = '\0';
      stop = 1;
    }
  }
}

int count_elements(s_str_el *element) {
  int count = 0;

  while (element) {
    count++;
    element = element->next;
  }

  return count;
}
