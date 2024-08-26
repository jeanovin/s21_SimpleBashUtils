#include "s21_grep.h"

int main(int argc, char **argv) {
  struct flags flag = {0};
  char findStr[4096] = {0};
  int options = 0;
  while ((options = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
    if (options == 'e') {
      flag.e = 1;
      snprintf(findStr, 4096, "%s", optarg);
    } else if (options == 'i') {
      flag.i = 1;
    } else if (options == 'v') {
      flag.v = 1;
    } else if (options == 'c') {
      flag.c = 1;
    } else if (options == 'l') {
      flag.l = 1;
    } else if (options == 'n') {
      flag.n = 1;
    } else if (options == 'h') {
      flag.h = 1;
    } else if (options == 'o') {
      flag.o = 1;
    } else if (options == 's') {
      flag.s = 1;
    } else if (options == 'f') {
      flag.f = 1;
      snprintf(findStr, 4096, "%s", optarg);
    }
  }
  if (argc >= 3) {
    char pattern[4096] = {0};
    int filePatt = 0;
    if (!flag.f && !flag.e) snprintf(pattern, 4096, "%s", argv[optind++]);
    if (flag.f) filePatt = openFile(pattern, findStr);
    if (!flag.f && flag.e) snprintf(pattern, 4096, "%s", findStr);
    if (filePatt != -1) {
      int fileCount = 0;
      if (argc - optind > 1) fileCount = 1;
      for (int i = optind; i < argc; i++) {
        if (fileCount && !flag.h && !flag.l) printf("%s:", argv[i]);
        Grep(&flag, pattern, argv[i]);
      }
    }
  } else {
    printf("usage: grep [-eivclnhsfo]\n");
  }
  return 0;
}

int openFile(char *pattern, char *fileName) {
  FILE *fp;
  fp = fopen(fileName, "r");
  int i = 0;
  if (fp != NULL) {
    int c;
    while ((c = fgetc(fp)) != EOF) {
      if (c == 13 || c == 10) pattern[i++] = '|';
      if (c != 13 && c != 10) pattern[i++] = c;
    }
  } else {
    printf("grep: Cannot open file.\n");
    i = -1;
  }
  if (pattern[i - 1] == '|') pattern[i - 1] = '\0';
  fclose(fp);
  return i;
}

void Grep(struct flags *flag, char *pattern, char *fileName) {
  int cflags = REG_EXTENDED;
  regex_t regular;
  FILE *fp;
  fp = fopen(fileName, "r");
  if (flag->i) cflags = REG_ICASE;
  if (fp != NULL) {
    regcomp(&regular, pattern, cflags);
    char textTest[4096] = {0};
    regmatch_t pmatch[1];
    int lineMatchCount = 0;
    int lineNum = 1;
    int maxMatch = 5;
    while (fgets(textTest, 4095, fp) != NULL) {
      char *current = textTest;
      int match = 0;
      int success = regexec(&regular, textTest, 1, pmatch, 0);
      if (strchr(textTest, '\n') == NULL) strcat(textTest, "\n");
      if (success == 0 && !flag->v) match = 1;
      if (success == REG_NOMATCH && flag->v) match = 1;
      if (match && !flag->l && !flag->c && flag->n) printf("%d:", lineNum);
      if (match && !flag->l && !flag->c && !flag->o) printf("%s", textTest);
      if (match && flag->o) {
        for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
          printf("%c", textTest[i]);
        }
        printf("\n");
        int offset = pmatch[0].rm_eo;
        current += offset;
        for (int m = 0; m < maxMatch; m++) {
          if (regexec(&regular, current, 1, pmatch, 0)) break;
          for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
            printf("%c", current[i]);
          }
          printf("\n");
          offset = pmatch[0].rm_eo;
          current += offset;
        }
      }
      lineMatchCount += match;
      lineNum++;
    }
    if (flag->l && lineMatchCount > 0) printf("%s\n", fileName);
    if (flag->c && !flag->l) printf("%d\n", lineMatchCount);
    regfree(&regular);
    fclose(fp);
  } else {
    if (!flag->s) perror(fileName);
  }
}