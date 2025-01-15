#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int res_code = 0;

  if (argc != 4) {
    fprintf(stderr, "Usage: ./create_long_line FILE CHAR LEN");
    res_code = -1;
  }

  if (!res_code) {
    FILE *f = fopen(argv[1], "a");

    if (f) {
      char c = atoi(argv[2]);
      int len = atoi(argv[3]);
      for (int i = 0; i < len; i++) {
        fputc(c, f);
      }
      fputc('\n', f);
      fclose(f);
    } else {
      res_code = -1;
    }
  }

  return res_code;
}
