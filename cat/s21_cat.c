#include "s21_cat.h"

#include "../common/common.h"

int main(int argc, char *argv[]) {
  int error = 0;
  if (argc > 1) {
    option flag = {0};
    parser(argc, argv, &flag, &error);
    if (error == 0) {
      process_file(argc, argv, flag);
    }
  }

  if (error != 0 && error != 2) {
    print_err(error);
  }

  return 0;
}

void process_file(int argc, char *argv[], option opt) {
  int count = 1;
  int num = 0;
  while (count != argc) {
    if (argv[count][0] != '-') {
      FILE *file;
      file = fopen(argv[count], "r");
      if (file != NULL) {
        print(file, opt, &num);
        fclose(file);
      } else {
        print_err(2);
      }
    }
    count++;
  }
}

void parser(int argc, char *argv[], option *opt, int *error) {
  int count = 1;
  while (count != argc) {
    if (argv[count][0] == '-' && argv[count][1] != '-') {
      for (int i = 1; i < (int)strlen(argv[count]); i++) {
        check_short(argv, count, i, opt, error);
      }
    } else if (argv[count][0] == '-' && argv[count][1] == '-') {
      check_long(argv, count, opt, error);
    }
    count++;
  }
}

void check_short(char *argv[], int count, int i, option *opt, int *error) {
  if (argv[count][i] == 'n' && opt->opt_b == 0) {
    opt->opt_n = 1;
  }
  if (argv[count][i] == 'b') {
    opt->opt_b = 1;
    opt->opt_n = 0;
  }
  if (argv[count][i] == 's') {
    opt->opt_s = 1;
  }
  if (argv[count][i] == 'E') {
    opt->opt_e = 1;
  }
  if (argv[count][i] == 'e') {
    opt->opt_e = 1;
    opt->opt_v = 1;
  }
  if (argv[count][i] == 'T') {
    opt->opt_t = 1;
  }
  if (argv[count][i] == 't') {
    opt->opt_t = 1;
    opt->opt_v = 1;
  }
  if (argv[count][i] == 'v') {
    opt->opt_v = 1;
  }
  if (argv[count][i] != 'n' && argv[count][i] != 'b' && argv[count][i] != 's' &&
      argv[count][i] != 'E') {
    if (argv[count][i] != 'e' && argv[count][i] != 'T' &&
        argv[count][i] != 't' && argv[count][i] != 'v')
      *error = 1;
  }
}

void check_long(char *argv[], int count, option *opt, int *error) {
  if (!strcmp(argv[count], "--number-nonblank")) {
    opt->opt_b = 1;
    opt->opt_n = 0;
  }
  if (!strcmp(argv[count], "--number") && opt->opt_b == 0) {
    opt->opt_n = 1;
  }
  if (!strcmp(argv[count], "--squeeze-blank")) {
    opt->opt_s = 1;
  }
  if (strcmp(argv[count], "--number-nonblank") &&
      strcmp(argv[count], "--number") &&
      strcmp(argv[count], "--squeeze-blank")) {
    *error = 1;
  }
}

void print(FILE *file, option opt, int *num) {
  int current_ch = fgetc(file), future_ch = '\0';
  if (current_ch != EOF) {
    int first_input = 0;
    print_num(num, opt, current_ch, future_ch, first_input);
    first_input = 1;
    while ((future_ch = fgetc(file)) != EOF) {
      squeeze(current_ch, &future_ch, file, opt, num, first_input);
      print_ch(current_ch, opt);
      if (future_ch != EOF) {
        print_num(num, opt, current_ch, future_ch, first_input);
      }
      current_ch = future_ch;
    }
    if (current_ch != EOF) {
      print_ch(current_ch, opt);
    }
  }
}

void print_num(int *num, option opt, int current_ch, int future_ch,
               int first_input) {
  if (current_ch == '\n' || first_input == 0) {
    if (opt.opt_n == 1 || (opt.opt_b == 1 && future_ch != '\n')) {
      (*num)++;
      printf("%6d\t", *num);
    }
  }
}

void squeeze(int current_ch, int *future_ch, FILE *file, option opt, int *num,
             int first_input) {
  if (current_ch == '\n' && *future_ch == '\n' && opt.opt_s == 1) {
    while (*future_ch == '\n') {
      *future_ch = fgetc(file);
    }
    opt.opt_e ? printf("$\n") : printf("\n");
    print_num(num, opt, '\n', current_ch, first_input);
  }
}

void print_ch(int current_ch, option opt) {
  if (opt.opt_v == 1) {
    if (current_ch > 127) {
      if (current_ch >= 160 && current_ch < 255) {
        printf("M-%c", current_ch - 128);
      } else if (current_ch == 255) {
        printf("M-^%c", current_ch - 192);
      } else {
        printf("M-^%c", current_ch - 64);
      }
    } else if (current_ch >= 0 && current_ch < 32 && current_ch != 10 &&
               current_ch != 9) {
      printf("^%c", current_ch + 64);
    } else if (current_ch == 127) {
      printf("^%c", current_ch - 64);
    } else if (current_ch == 10 && opt.opt_e == 1) {
      printf("$\n");
    } else if (current_ch == 9 && opt.opt_t == 1) {
      printf("^I");
    } else {
      printf("%c", current_ch);
    }
  } else if (opt.opt_e == 1) {
    if (current_ch == 10) {
      printf("$\n");
    } else if (current_ch == 9 && opt.opt_t == 1) {
      printf("^I");
    } else {
      printf("%c", current_ch);
    }
  } else if (opt.opt_t == 1) {
    if (current_ch == 9) {
      printf("^I");
    } else {
      printf("%c", current_ch);
    }
  } else {
    printf("%c", current_ch);
  }
}