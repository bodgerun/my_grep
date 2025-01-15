#include "my_grep_match.h"

int match_pats(s_conf *conf) {
  int res_code = 1, match = 1;
  s_str_el *file = conf->strs;

  conf->files_count = count_elements(conf->strs);

  while (file && match != -1) {
    FILE *f = fopen(file->str, "r");

    if (f) {
      match = process_file(f, conf, file->str);
      if (match == 0 && res_code == 1) {
        res_code = 0;
      } else if (match == -1) {
        res_code = -1;
      }
      fclose(f);
    } else {
      res_code = -1;
      if (!conf->ops.s) {
        fprintf(stderr, "my_grep: %s: No such file or directory\n", file->str);
      }
    }

    file = file->next;
  }

  return res_code;
}

int process_file(FILE *f, s_conf *conf, const char *fname) {
  int res_code = 1, stop = 0;
  char buff[BUFF_SIZE];
  size_t max_len = BUFF_SIZE;
  s_fdata fdata;
  fdata.fname = fname;
  fdata.matched_count = 0;
  fdata.lnum = 0;
  fdata.line = calloc(max_len, sizeof(*fdata.line));

  if (!fdata.line) {
    res_code = -1;
  }

  while (fgets(buff, BUFF_SIZE, f) && !stop && res_code != -1) {
    if (max_len - strlen(fdata.line) < BUFF_SIZE) {
      res_code = redouble_str(&fdata.line, &max_len);
    }
    if (res_code != -1) {
      strcat(fdata.line, buff);
      if (strchr(buff, '\n')) {
        res_code = process_line(&fdata, conf, &stop);
        fdata.line[0] = '\0';
      }
    }
  }

  if (res_code != -1 && strlen(fdata.line)) {
    res_code = process_line(&fdata, conf, &stop);
  }

  free(fdata.line);

  if (res_code != -1) {
    if (conf->ops.c || conf->ops.l) {
      out_file(&fdata, conf);
    }
    res_code = fdata.matched_count ? 0 : 1;
  }

  return res_code;
}

int process_line(s_fdata *fdata, s_conf *conf, int *stop) {
  int res_code;
  fdata->lnum++;
  fdata->substrs = NULL;

  if (conf->mode == all) {
    res_code = 0;
  } else if (conf->mode == none) {
    res_code = 1;
  } else {
    res_code = get_match(fdata, conf);
  }

  if (!res_code) {
    fdata->matched_count++;
    if (conf->ops.l) {
      *stop = 1;
#ifdef __linux__
    } else if (conf->ops.o && conf->ops.v) {
      ;
#endif
    } else if (conf->ops.o && conf->mode == all) {
      ;
    } else if (conf->ops.c || conf->ops.l) {
      ;
    } else {
      out_line(fdata, conf);
    }
  }

  free_list_strs(fdata->substrs);

  return res_code;
}

int get_match(s_fdata *fdata, s_conf *conf) {
  s_comp_el *pat_comp = conf->pats_comp;
  int active_o = conf->ops.o && !(conf->ops.c || conf->ops.l || conf->ops.v);
  int res_code = REG_NOMATCH;

  while (pat_comp && res_code == REG_NOMATCH) {
    if (!active_o) {
      res_code = regexec(&(pat_comp->pat), fdata->line, 0, NULL, 0);
    } else {
      res_code = get_all_substrs(&(pat_comp->pat), fdata);
    }
    pat_comp = pat_comp->next;
  }

  if (res_code != -1) {
    if (active_o && fdata->substrs) {
      res_code = 0;
    } else if (res_code == 0 && !conf->ops.v) {
      res_code = 0;
    } else if (res_code == REG_NOMATCH && conf->ops.v) {
      res_code = 0;
    } else {
      res_code = REG_NOMATCH;
    }
  }

  return res_code;
}

int get_all_substrs(const regex_t *preg, s_fdata *fdata) {
  size_t nmatch = 1;
  regmatch_t pmatch[nmatch];

  int res_code = regexec(preg, fdata->line, nmatch, pmatch, 0);

  if (!res_code) {
    size_t max_len = strlen(fdata->line);
    char buff[max_len];
    const char *s = fdata->line;

    do {
      s += pmatch[0].rm_so;
      size_t len = pmatch[0].rm_eo - pmatch[0].rm_so;
      strncpy(buff, s, len);
      buff[len] = '\0';
      res_code = append_to_str_list(buff, &(fdata->substrs));
      if (!res_code) {
        s += len;
        res_code = regexec(preg, s, nmatch, pmatch, 0);
      }
    } while (!res_code && (size_t)(s - fdata->line) < max_len);
  }

  if (res_code != -1) {
    res_code = REG_NOMATCH;
  }

  return res_code; /* -1 | 1 */
}
