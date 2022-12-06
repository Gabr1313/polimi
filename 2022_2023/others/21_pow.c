#include <stdio.h>
#include <stdlib.h>

typedef unsigned long int u8;

int main(int argc, char *argv[]) {
  u8 base, exp, ris;
  char *check;

  if (argc == 3) {
    base = strtoul(argv[1], &check, 10);
    if (check[0]){
      printf("%s is not a number\n", argv[1]);
      return 0;
    }
    exp = strtoul(argv[2], &check, 10);
    if (check[0]){
      printf("%s is not a number\n", argv[2]);
      return 0;
    }

    ris = 1;
    if (exp & 1) {
      ris *= base;
    }
    exp >>= 1;
    while (exp) {
      base *= base;
      if (exp & 1) {
        ris *= base;
      }
      exp >>= 1;
    }

    printf("%ld\n", ris);

  } else
    printf("Usage: %s base exp\n", argv[0]);
  return 0;
}
