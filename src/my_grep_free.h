#ifndef MY_GREP_FREE_H
#define MY_GREP_FREE_H

#include <regex.h>
#include <stdlib.h>

#include "my_grep_types.h"

void free_all(s_conf *conf);
void free_list_strs(s_str_el *strs);
void free_list_pats_comp(s_comp_el *pats_comp);

#endif
