#include "s21_cat.h"

int main(int argc, char* argv[]) {
  struct flags flag = {0};
  int error = 0;
  int options = 0;
  while ((options = getopt_long(argc, argv, "beEstTnv", long_options, NULL)) !=
         -1) {
    if (options == 'b') {
      flag.b = 1;
    } else if (options == 'e') {
      flag.e = 1;
      flag.v = 1;
    } else if (options == 'E') {
      flag.e = 1;
    } else if (options == 'n') {
      flag.n = 1;
    } else if (options == 's') {
      flag.s = 1;
    } else if (options == 'n') {
      flag.n = 1;
    } else if (options == 't') {
      flag.t = 1;
      flag.v = 1;
    } else if (options == 'T') {
      flag.t = 1;
    } else if (options == 'v') {
      flag.v = 1;
    } else {
      printf("cat: invalid option -- %c", options);
      error = 1;
    }
  }
  if (!error) {
    for (; optind < argc; optind++) {
      FILE* fp = NULL;
      fp = fopen(argv[optind], "r+");
      if (!fp) {
        printf("cat: No such file or directory");
      } else {
        catFunc(&flag, fp);
        fclose(fp);
      }
    }
    return 0;
  }
}

void catFunc(struct flags* flag, FILE* fp) {
  int x_now, x_prev = 1;
  int empty_count = 0, string_count = 1;
  int first_string = 1;
  while ((x_now = fgetc(fp)) != EOF) {
    if (flag->s) {
      if (x_now == '\n') empty_count++;
      if (x_now != '\n') empty_count = 0;
    }
    if (x_now == '\n' && (!flag->s || empty_count < 3)) {
      if (flag->n && (x_prev == '\n' || first_string == 1))
        printf("%6d\t", string_count++);
      if (flag->e) printf("$");
      printf("%c", x_now);
    }
    if (x_now != '\n') {
      if ((x_prev == '\n' || first_string == 1) && (flag->n || flag->b))
        printf("%6d\t", string_count++);
      if (x_now < 32 && x_now != 9 && x_now != 10 && flag->v)
        printf("^%c", x_now + 64);
      else if (x_now > 127 && x_now < 160 && flag->v)
        printf("M-^%c", x_now - 64);
      else if (x_now == 127 && flag->v)
        printf("^%c", x_now - 64);
      else if (x_now == '\t' && flag->t)
        printf("^I");
      else
        printf("%c", x_now);
    }
    x_prev = x_now;
    first_string = 0;
  }
}
