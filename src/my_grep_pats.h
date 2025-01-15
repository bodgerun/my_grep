#ifndef MY_GREP_PATS_H
#define MY_GREP_PATS_H

#include <regex.h>
#include <stdlib.h>

#include "my_grep_types.h"
#include "my_grep_utils.h"

int prepare_pats(s_conf *conf);
void check_pats(s_conf *conf);
void check_empty_pats(s_conf *conf);
void check_duplicate_pats(s_conf *conf);
int compile_pats(s_conf *conf);

#endif
