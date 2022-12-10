#include <stdio.h>
#include <stdlib.h>
#include "3.c"

#define BASE 10


int main(int argc, char* argv[]) {
  if (argc == 2) {
    printf("%d\n", count_cfr_div(atoi(argv[1])));
  } else
    printf("Usage: %s int\n", argv[0]);

  return 0;
}
