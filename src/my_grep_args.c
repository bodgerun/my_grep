#include "my_grep_args.h"

int read_args(int argc, char **argv, s_conf *conf) {
  int res_code = 0;
  int flag = flag_any; /* what type of arg is expected now */

  for (int i = 1; i < argc && !res_code; i++) {
    int arg_code = classify_arg(argv[i], flag);
    flag = flag_any;

    switch (arg_code) {
      case arg_op:
        res_code = set_options(argv[i], conf, &flag);
        break;
      case arg_e_pat:
        res_code = append_to_str_list(argv[i], &conf->pats_lit);
        break;
      case arg_f_pat:
        res_code = read_file_with_patterns(argv[i], &conf->pats_lit);
        break;
      case arg_str:
        res_code = append_to_str_list(argv[i], &conf->strs);
    }
  }

  if (!res_code) {
    res_code = check_flag(flag);
  }

  return res_code;
}

int classify_arg(const char *arg, int flag) {
  int res;

  if (flag == flag_e_pat) {
    res = arg_e_pat;
  } else if (flag == flag_f_pat) {
    res = arg_f_pat;
  } else if (arg[0] == '-') {
    res = arg_op;
  } else {
    res = arg_str;
  }

  return res;
}

int check_flag(int flag) {
  int res_code = -1;

  if (flag == flag_e_pat) {
    fprintf(stderr, "my_grep: option requires an argument -- e\n");
  } else if (flag == flag_f_pat) {
    fprintf(stderr, "my_grep: option requires an argument -- f\n");
  } else {
    res_code = 0;
  }

  return res_code;
}

int set_options(const char *op, s_conf *conf, int *flag) {
  int res_code = -1, stop = 0;

  for (int i = 1; op[i] && !stop; i++) {
    res_code = 0;
    switch (op[i]) {
      case 'c':
        conf->ops.c = 1;
        break;
      case 'e':
        process_e(op + i, conf, flag);
        stop = 1;
        break;
      case 'f':
        conf->ops.f = 1;
        process_f(op + i, conf, flag);
        stop = 1;
        break;
      case 'h':
        conf->ops.h = 1;
        break;
      case 'i':
        conf->ops.i = 1;
        break;
      case 'l':
        conf->ops.l = 1;
        break;
      case 'n':
        conf->ops.n = 1;
        break;
      case 'o':
        conf->ops.o = 1;
        break;
      case 's':
        conf->ops.s = 1;
        break;
      case 'v':
        conf->ops.v = 1;
        break;
      default:
        fprintf(stderr, "my_grep: invalid option -- %c\n", op[i]);
        res_code = -1;
        stop = 1;
    }
  }

  return res_code;
}

int process_e(const char *str, s_conf *conf, int *flag) {
  int res_code = 0;

  if (!str[1]) {
    *flag = flag_e_pat;
  } else {
    res_code = append_to_str_list(str + 1, &(conf->pats_lit));
  }

  return res_code;
}

int process_f(const char *str, s_conf *conf, int *flag) {
  int res_code = 0;

  if (!str[1]) {
    *flag = flag_f_pat;
  } else {
    res_code = read_file_with_patterns(str + 1, &(conf->pats_lit));
  }

  return res_code;
}

int append_to_str_list(const char *new_str, s_str_el **strs) {
  while (*strs) {
    strs = &(*strs)->next;
  }

  return add_str(new_str, strs);
}

int add_str(const char *new_str, s_str_el **strs) {
  int res_code = -1;

  if (!*strs) {
    s_str_el *tmp = malloc(sizeof(*tmp));
    if (tmp) {
      tmp->str = calloc(strlen(new_str) + 1, sizeof(*tmp->str));
      if (tmp->str) {
        strcpy(tmp->str, new_str);
        tmp->next = NULL;
        *strs = tmp;
        res_code = 0;
      } else {
        free(tmp);
      }
    }
  }

  return res_code;
}

int read_file_with_patterns(const char *fname, s_str_el **strs) {
  int res_code = 0;
  FILE *f = fopen(fname, "r");

  if (f) {
    res_code = import_patterns(f, strs);
    fclose(f);
  } else {
    fprintf(stderr, "my_grep: %s: No such file or directory\n", fname);
    res_code = -1;
  }

  return res_code;
}

int import_patterns(FILE *f, s_str_el **strs) {
  int res_code = 0;
  char buff[BUFF_SIZE];
  size_t max_len = BUFF_SIZE;
  char *new_pat = calloc(max_len, sizeof(*new_pat));

  if (!new_pat) {
    res_code = -1;
  }

  while (fgets(buff, BUFF_SIZE, f) && !res_code) {
    if (new_pat[0] && max_len - strlen(new_pat) < BUFF_SIZE) {
      res_code = redouble_str(&new_pat, &max_len);
    }
    if (!res_code) {
      strcat(new_pat, buff);
      if (strchr(buff, '\n')) {
        remove_newline(new_pat);
        res_code = append_to_str_list(new_pat, strs);
        new_pat[0] = '\0';
      }
    }
  }

  if (!res_code && strlen(new_pat)) {
    res_code = append_to_str_list(new_pat, strs);
  }

  free(new_pat);

  return res_code;
}
