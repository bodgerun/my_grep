#ifndef MY_GREP_ARGS_H
#define MY_GREP_ARGS_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_grep_types.h"
#include "my_grep_utils.h"

int read_args(int argc, char **argv, s_conf *conf);
int classify_arg(const char *arg, int flag);
int check_flag(int flag);
int set_options(const char *op, s_conf *conf, int *flag);
int process_e(const char *str, s_conf *conf, int *flag);
int process_f(const char *str, s_conf *conf, int *flag);
int append_to_str_list(const char *new_str, s_str_el **strs);
int add_str(const char *new_str, s_str_el **strs);
int read_file_with_patterns(const char *fname, s_str_el **strs);
int import_patterns(FILE *f, s_str_el **strs);

#endif
