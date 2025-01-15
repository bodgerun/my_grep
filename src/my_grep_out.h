#ifndef MY_GREP_OUT_H
#define MY_GREP_OUT_H

#include <stdio.h>
#include <string.h>

#include "my_grep_types.h"

void out_fname(const s_fdata *fdata, const s_conf *conf);
void out_lnum(const s_fdata *fdata, const s_conf *conf);
void out_line(const s_fdata *fdata, const s_conf *conf);
void out_file(const s_fdata *fdata, const s_conf *conf);

#endif
