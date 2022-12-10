#define BASE 10
#include <stdio.h>


int count_cfr_div(int n) {
  int div, count, tmp;

  tmp = n;
  count = 0;
  while (tmp > 0) {
    div = tmp % BASE;
    if (!(n % div))
      count ++;
    tmp /= BASE;
  }

  return count;
}
