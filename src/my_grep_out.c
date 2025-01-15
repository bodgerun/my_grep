#include "my_grep_out.h"

void out_fname(const s_fdata *fdata, const s_conf *conf) {
  if (!conf->ops.h && conf->files_count > 1) {
    printf("%s:", fdata->fname);
  }
}

void out_lnum(const s_fdata *fdata, const s_conf *conf) {
  if (conf->ops.n) {
    printf("%d:", fdata->lnum);
  }
}

void out_line(const s_fdata *fdata, const s_conf *conf) {
  if (!conf->ops.o || conf->ops.v) {
    out_fname(fdata, conf);
    out_lnum(fdata, conf);

    printf("%s", fdata->line);
    if (!strchr(fdata->line, '\n')) {
      printf("\n");
    }
  } else {
    s_str_el *substr = fdata->substrs;

    while (substr) {
      out_fname(fdata, conf);
      out_lnum(fdata, conf);

      printf("%s\n", substr->str);
      substr = substr->next;
    }
  }
}

void out_file(const s_fdata *fdata, const s_conf *conf) {
#ifdef __linux__
  if (conf->ops.c && !conf->ops.l && conf->mode != none)
#else
  if (conf->ops.c)
#endif
  {
    if (conf->files_count > 1 && !conf->ops.h) {
      printf("%s:", fdata->fname);
    }
    printf("%d\n", fdata->matched_count);
  }

  if (conf->ops.l && fdata->matched_count) {
    printf("%s\n", fdata->fname);
  }
}
