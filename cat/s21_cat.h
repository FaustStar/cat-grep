#ifndef S21_CAT_H
#define S21_CAT_H

#include <stdio.h>
#include <string.h>

typedef struct {
  int opt_n;
  int opt_b;
  int opt_s;
  int opt_e;
  int opt_t;
  int opt_v;
} option;

void process_file(int argc, char *argv[], option opt);
void parser(int argc, char *argv[], option *opt, int *error);
void check_short(char *argv[], int count, int i, option *opt, int *error);
void check_long(char *argv[], int count, option *opt, int *error);
void print(FILE *file, option opt, int *num);
void print_num(int *num, option opt, int current_ch, int future_ch,
               int first_input);
void squeeze(int current_ch, int *future_ch, FILE *file, option opt, int *num,
             int first_input);
void print_ch(int current_ch, option opt);

#endif