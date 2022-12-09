#include <stdio.h>
#include <stdlib.h>

#define BASE 10

int count_cfr_div(int n) {
  int div, count, tmp;

  tmp = n;
  count = 0;
  while (tmp > 0) {
    div = tmp % BASE;
    if (!(n % div)) count++;
    tmp /= BASE;
  }

  return count;
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    printf("%d\n", count_cfr_div(atoi(argv[1])));
  } else
    printf("Usage: %s int\n", argv[0]);

  return 0;
}
