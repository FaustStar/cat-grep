#ifndef S21_GREP_H
#define S21_GREP_H

#define _GNU_SOURCE
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ROW_COUNT 1000
#define MAX_LENGTH 512
#define MAX_LIMIT 1000

typedef struct {
  int opt_e;
  int opt_i;
  int opt_v;
  int opt_c;
  int opt_l;
  int opt_n;
  int opt_h;
  int opt_s;
  int opt_f;
  int opt_o;
  int file_count;
  char *file_name[MAX_LIMIT];
  int pattern_count;
  char *pattern[MAX_LIMIT];
  int shadow_e;
  int shadow_f;
} option;

void process_data(option opt);
void init_data(int argc, char *argv[], option *opt, int *error,
               char patterns[][MAX_LENGTH], int n, int m, int *count_row);
void check_input(int argc, char *argv[], option *opt, int *error);
void find_spec_flag(char *argv[], int count, int i, option *opt);
void find_file(char *argv[], int count, option *opt, int *error);
int count_ch(char *str, char ch);
void parser(int argc, char *argv[], option *opt, int *error,
            char patterns[][MAX_LENGTH], int n, int m, int *count_row);
void check_short(char *argv[], int count, int i, option *opt, int *error);
void find_pattern(option *opt, int argc, char *argv[], int count, int *i,
                  int *error, char patterns[][MAX_LENGTH], int n, int m,
                  int *count_row);
void read_file(FILE *file, int *error, option *opt, char patterns[][MAX_LENGTH],
               int n, int m, int *count_row);
void change_ch(char patterns[][MAX_LENGTH], int count_row);
void search(FILE *file, option opt, int count);
void print_reg(option opt, regex_t *regex, char *line, int count, int num);
void print_res(int success, int *success_num, int num, option opt, char *line,
               int *over, int inversion, int count);
int check_inversion(int opt_v);
int check_flag_compilation(int opt_i);
void print_file_name(option opt, int count);
void print_num(int num, int opt_n);
void print_success_num(int success_num, option opt, int count);

#endif