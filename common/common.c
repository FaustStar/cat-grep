#include "common.h"

#include <stdio.h>

void print_err(int error) {
  switch (error) {
    case 1:
      printf("error: invalid option :(\n");
      break;
    case 2:
      printf("error: no such file or directory (what you want to see) :(\n");
      break;
    case 3:
      printf("error: option -e requires an argument :(\n");
      break;
    case 4:
      printf("error: option -f requires an argument :(\n");
      break;
    case 5:
      printf(
          "error: no such file or directory (where patterns should be in) "
          ":(\n");
      break;
    case 6:
      printf("error: too many patterns :(\n");
      break;
    case 7:
      printf("error: too many files to search in :(\n");
      break;
    case 8:
      printf("error: grep [OPTION]... PATTERNS [FILE]...\n");
      break;
  }
}