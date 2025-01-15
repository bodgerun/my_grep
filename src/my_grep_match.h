#ifndef MY_GREP_MATCH_H
#define MY_GREP_MATCH_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_grep_args.h"
#include "my_grep_free.h"
#include "my_grep_out.h"
#include "my_grep_types.h"
#include "my_grep_utils.h"

int match_pats(s_conf *conf);
int process_file(FILE *f, s_conf *conf, const char *fname);
int process_line(s_fdata *fdata, s_conf *conf, int *stop);
int get_match(s_fdata *fdata, s_conf *conf);
int get_all_substrs(const regex_t *preg, s_fdata *fdata);

#endif
