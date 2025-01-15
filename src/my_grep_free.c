#include "my_grep_free.h"

void free_all(s_conf *conf) {
  free_list_strs(conf->pats_lit);
  free_list_pats_comp(conf->pats_comp);
  free_list_strs(conf->strs);
}

void free_list_strs(s_str_el *strs) {
  if (strs) {
    free_list_strs(strs->next);
    free(strs->str);
    free(strs);
  }
}

void free_list_pats_comp(s_comp_el *pats_comp) {
  if (pats_comp) {
    free_list_pats_comp(pats_comp->next);
    regfree(&(pats_comp->pat));
    free(pats_comp);
  }
}
