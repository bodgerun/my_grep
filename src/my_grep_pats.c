#include "my_grep_pats.h"

int prepare_pats(s_conf *conf) {
  int res_code = 0;

  check_pats(conf);

  if (conf->mode == selected) {
    check_empty_pats(conf);
  }

  if (conf->mode == selected) {
    check_duplicate_pats(conf);
  }

  if (conf->mode == selected) {
    res_code = compile_pats(conf);
  }

  return res_code;
}

void check_pats(s_conf *conf) {
  if (!conf->pats_lit) {
    if (conf->ops.f || !conf->strs) {
      conf->mode = none;
    } else {
      conf->pats_lit = conf->strs;
      conf->strs = conf->strs->next;
      conf->pats_lit->next = NULL;
    }
  }
}

void check_empty_pats(s_conf *conf) {
  s_str_el *ptr = conf->pats_lit;

  while (ptr && conf->mode == selected) {
    if (ptr->str[0]) {
      ptr = ptr->next;
    } else {
      conf->mode = conf->ops.v ? none : all;
    }
  }
}

void check_duplicate_pats(s_conf *conf) {
  int ops_i = conf->ops.i;
  s_str_el *old_pats_lit = conf->pats_lit;
  s_str_el *new_pats_lit = NULL;

  while (old_pats_lit) {
    int dupl = 0;
    s_str_el **ptr = &new_pats_lit;

    while (*ptr && !dupl) {
      dupl = is_duplicate((*ptr)->str, old_pats_lit->str, ops_i);
      if (!dupl) {
        ptr = &(*ptr)->next;
      }
    }

    if (dupl) {
      s_str_el *tmp = old_pats_lit;
      old_pats_lit = old_pats_lit->next;
      free(tmp->str);
      free(tmp);
    } else {
      *ptr = old_pats_lit;
      old_pats_lit = old_pats_lit->next;
      (*ptr)->next = NULL;
    }
  }

  conf->pats_lit = new_pats_lit;
}

int compile_pats(s_conf *conf) {
  int res_code = 0;
  int cflags = REG_NEWLINE;
  s_str_el *cur_pat_lit = conf->pats_lit;
  s_comp_el **cur_pat_comp = &conf->pats_comp;

  if (conf->ops.i) {
    cflags |= REG_ICASE;
  }

  while (cur_pat_lit && !res_code) {
    s_comp_el *tmp = malloc(sizeof(*tmp));
    if (tmp) {
      res_code = regcomp(&tmp->pat, cur_pat_lit->str, cflags);
      tmp->next = NULL;
      *cur_pat_comp = tmp;
      cur_pat_comp = &(*cur_pat_comp)->next;
      cur_pat_lit = cur_pat_lit->next;
    } else {
      res_code = -1;
    }
  }

  return res_code;
}
