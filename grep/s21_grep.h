#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

struct flags {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
};

int openFile(char *pattern, char *fileName);
void Grep(struct flags *flags, char *pattern, char *fileName);

#endif  // S21_GREP_H