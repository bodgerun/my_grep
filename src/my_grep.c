#include "my_grep_args.h"
#include "my_grep_free.h"
#include "my_grep_match.h"
#include "my_grep_pats.h"
#include "my_grep_types.h"

int main(int argc, char **argv) {
  s_conf conf = {{0, 0, 0, 0, 0, 0, 0, 0, 0}, NULL, NULL, NULL, selected, 0};

  int res_code = read_args(argc, argv, &conf);

  if (!res_code) {
    res_code = prepare_pats(&conf);
  }

  if (!res_code) {
    res_code = match_pats(&conf);
  }

  free_all(&conf);

  return res_code;
}
