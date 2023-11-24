#include "s21_grep.h"

#include "../common/common.h"

int main(int argc, char *argv[]) {
  int error = 0, count_row = 0;
  if (argc > 1) {
    option data;
    char patterns[ROW_COUNT][MAX_LENGTH];
    init_data(argc, argv, &data, &error, patterns, ROW_COUNT, MAX_LENGTH,
              &count_row);
    if (error == 0) {
      process_data(data);
    }
  } else {
    error = 8;
  }
  if (error != 0 && error != 2) {
    print_err(error);
  }
  return 0;
}

void process_data(option opt) {
  for (int i = 0; i < opt.file_count; i++) {
    FILE *file = fopen(opt.file_name[i], "r");
    if (file != NULL) {
      search(file, opt, i);
      fclose(file);
    } else if (opt.opt_s != 1) {
      print_err(2);
    }
  }
}

void init_data(int argc, char *argv[], option *opt, int *error,
               char patterns[][MAX_LENGTH], int n, int m, int *count_row) {
  opt->opt_e = 0;
  opt->opt_i = 0;
  opt->opt_v = 0;
  opt->opt_c = 0;
  opt->opt_l = 0;
  opt->opt_n = 0;
  opt->opt_h = 0;
  opt->opt_s = 0;
  opt->opt_f = 0;
  opt->opt_o = 0;
  opt->shadow_e = 0;
  opt->shadow_f = 0;
  opt->pattern_count = 0;
  opt->file_count = 0;
  check_input(argc, argv, opt, error);
  parser(argc, argv, opt, error, patterns, n, m, count_row);
}

void check_input(int argc, char *argv[], option *opt, int *error) {
  int count = 1;
  while (count != argc) {
    if (argv[count][0] == '-') {
      for (int i = 1; i < (int)strlen(argv[count]); i++) {
        find_spec_flag(argv, count, i, opt);
      }
    }
    count++;
  }
  count = 1;
  if (opt->shadow_e == 0 && opt->shadow_f == 0) {
    int end_search = 0;
    while (count != argc && end_search == 0) {
      if (argv[count][0] != '-') {
        opt->pattern[opt->pattern_count] = argv[count];
        (opt->pattern_count)++;
        end_search++;
      }
      count++;
    }
  }
  while (count != argc) {
    if (argv[count - 1][0] != '-') {
      find_file(argv, count, opt, error);
    } else if (argv[count - 1][(int)strlen(argv[count - 1]) - 1] != 'e') {
      if (argv[count - 1][(int)strlen(argv[count - 1]) - 1] != 'f') {
        find_file(argv, count, opt, error);
      } else if (count_ch(argv[count - 1], 'f') > 1 ||
                 count_ch(argv[count - 1], 'e') > 0) {
        find_file(argv, count, opt, error);
      }
    } else if (count_ch(argv[count - 1], 'e') > 1 ||
               count_ch(argv[count - 1], 'f') > 0) {
      find_file(argv, count, opt, error);
    }
    count++;
  }
}

void find_spec_flag(char *argv[], int count, int i, option *opt) {
  if (argv[count][i] == 'e') {
    opt->shadow_e = 1;
  }
  if (argv[count][i] == 'f') {
    opt->shadow_f = 1;
  }
}

void find_file(char *argv[], int count, option *opt, int *error) {
  if (argv[count][0] != '-' && (opt->file_count) < MAX_LIMIT) {
    opt->file_name[opt->file_count] = argv[count];
    (opt->file_count)++;
  } else if ((opt->file_count) >= MAX_LIMIT) {
    *error = 7;
  }
}

int count_ch(char *str, char ch) {
  int res = 0;
  for (int i = 0; i < (int)strlen(str); i++) {
    if (str[i] == ch) {
      res++;
    }
  }
  return res;
}

void parser(int argc, char *argv[], option *opt, int *error,
            char patterns[][MAX_LENGTH], int n, int m, int *count_row) {
  int count = 1;
  while (count != argc) {
    if (argv[count][0] == '-') {
      for (int i = 1; i < (int)strlen(argv[count]); i++) {
        check_short(argv, count, i, opt, error);
        find_pattern(opt, argc, argv, count, &i, error, patterns, n, m,
                     count_row);
      }
      if (count + 1 != argc &&
          argv[count + 1] == opt->pattern[(opt->pattern_count) - 1]) {
        count++;
      }
    }
    count++;
  }
}

void check_short(char *argv[], int count, int i, option *opt, int *error) {
  if (argv[count][i] == 'e') {
    opt->opt_e = 1;
  }
  if (argv[count][i] == 'i') {
    opt->opt_i = 1;
  }
  if (argv[count][i] == 'v') {
    opt->opt_v = 1;
  }
  if (argv[count][i] == 'c') {
    opt->opt_c = 1;
  }
  if (argv[count][i] == 'l') {
    opt->opt_l = 1;
  }
  if (argv[count][i] == 'n') {
    opt->opt_n = 1;
  }
  if (argv[count][i] == 'h') {
    opt->opt_h = 1;
  }
  if (argv[count][i] == 's') {
    opt->opt_s = 1;
  }
  if (argv[count][i] == 'f') {
    opt->opt_f = 1;
  }
  if (argv[count][i] == 'o') {
    opt->opt_o = 1;
  }
  if (opt->opt_c == 1 && opt->opt_l == 1) {
    opt->opt_c = 0;
  }
  if (argv[count][i] != 'e' && argv[count][i] != 'i' && argv[count][i] != 'v' &&
      argv[count][i] != 'c' && argv[count][i] != 'l') {
    if (argv[count][i] != 'n' && argv[count][i] != 'h' &&
        argv[count][i] != 's' && argv[count][i] != 'f' &&
        argv[count][i] != 'o') {
      *error = 1;
    }
  }
}

void find_pattern(option *opt, int argc, char *argv[], int count, int *i,
                  int *error, char patterns[][MAX_LENGTH], int n, int m,
                  int *count_row) {
  if (opt->opt_e == 1) {
    if (*i + 1 != (int)strlen(argv[count]) &&
        (opt->pattern_count) < MAX_LIMIT) {
      opt->pattern[opt->pattern_count] = argv[count] + (*i) + 1;
      opt->opt_e = 0;
      (opt->pattern_count)++;
      *i = (int)strlen(argv[count]) - 1;
    } else if (count + 1 != argc && (opt->pattern_count) < MAX_LIMIT) {
      opt->pattern[opt->pattern_count] = argv[count + 1];
      opt->opt_e = 0;
      (opt->pattern_count)++;
    } else if ((opt->pattern_count) < MAX_LIMIT) {
      *error = 3;
    } else {
      *error = 6;
    }
  }
  if (opt->opt_f == 1) {
    if (*i + 1 != (int)strlen(argv[count])) {
      FILE *file = fopen(argv[count] + (*i) + 1, "r");
      read_file(file, error, opt, patterns, n, m, count_row);
      opt->opt_f = 0;
      *i = (int)strlen(argv[count]) - 1;
    } else if (count + 1 != argc) {
      FILE *file = fopen(argv[count + 1], "r");
      read_file(file, error, opt, patterns, n, m, count_row);
      opt->opt_f = 0;
    } else {
      *error = 4;
    }
  }
}

void read_file(FILE *file, int *error, option *opt, char patterns[][MAX_LENGTH],
               int n, int m, int *count_row) {
  if (file != NULL) {
    char *line = NULL;
    size_t len = 0;
    ssize_t read_n = 0;
    while ((read_n = getline(&line, &len, file)) != EOF &&
           (int)strlen(line) <= m && *count_row < n &&
           (opt->pattern_count) <= MAX_LIMIT) {
      if ((opt->pattern_count) != MAX_LIMIT) {
        strcpy(patterns[*count_row], line);
        opt->pattern[opt->pattern_count] = patterns[*count_row];
        (opt->pattern_count)++;
        change_ch(patterns, *count_row);
        (*count_row)++;
      } else {
        *error = 6;
      }
    }
    free(line);
    fclose(file);
  } else {
    *error = 5;
  }
}

void change_ch(char patterns[][MAX_LENGTH], int count_row) {
  if (patterns[count_row][0] != '\n') {
    patterns[count_row][(int)strlen(patterns[count_row]) - 1] = '\0';
  }
}

void search(FILE *file, option opt, int count) {
  int inversion = check_inversion(opt.opt_v);
  int regflag = check_flag_compilation(opt.opt_i);
  char *line = NULL;
  size_t len = 0;
  ssize_t read_n = 0;
  int num = 0, success_num = 0, over = 0;
  while (read_n != EOF && over != 1) {
    read_n = getline(&line, &len, file);
    if (line && read_n != EOF) {
      regex_t regex;
      num++;
      int success = REG_NOMATCH;
      for (int i = 0; i < opt.pattern_count && success != 0; i++) {
        regcomp(&regex, opt.pattern[i], regflag);
        success = regexec(&regex, line, 0, NULL, 0);
        print_reg(opt, &regex, line, count, num);
        regfree(&regex);
      }
      print_res(success, &success_num, num, opt, line, &over, inversion, count);
    }
  }
  free(line);
  print_success_num(success_num, opt, count);
}

void print_reg(option opt, regex_t *regex, char *line, int count, int num) {
  if (opt.opt_o == 1 && opt.opt_c != 1 && opt.opt_l != 1 && opt.opt_v != 1) {
    regmatch_t pmatch[1];
    char *temp = line;
    while (regexec(regex, temp, 1, pmatch, 0) == 0) {
      print_file_name(opt, count);
      print_num(num, opt.opt_n);
      printf("%.*s\n", (int)(pmatch[0].rm_eo - pmatch[0].rm_so),
             temp + pmatch[0].rm_so);
      temp += pmatch[0].rm_eo;
    }
  }
}

void print_res(int success, int *success_num, int num, option opt, char *line,
               int *over, int inversion, int count) {
  if (success == inversion) {
    (*success_num)++;
    if (opt.opt_l == 1) {
      printf("%s\n", opt.file_name[count]);
      *over = 1;
    }
    if (opt.opt_c != 1 && *over != 1 && opt.opt_o != 1) {
      print_file_name(opt, count);
      print_num(num, opt.opt_n);
      printf("%s", line);
    }
  }
}

int check_inversion(int opt_v) { return opt_v == 1 ? REG_NOMATCH : 0; }

int check_flag_compilation(int opt_i) {
  return opt_i == 1 ? REG_ICASE : REG_NEWLINE;
}

void print_file_name(option opt, int count) {
  if (opt.file_count > 1 && opt.opt_h != 1) {
    printf("%s:", opt.file_name[count]);
  }
}

void print_num(int num, int opt_n) {
  if (opt_n == 1) {
    printf("%d:", num);
  }
}

void print_success_num(int success_num, option opt, int count) {
  if (opt.opt_c == 1) {
    print_file_name(opt, count);
    printf("%d\n", success_num);
  }
}