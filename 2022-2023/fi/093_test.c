#include "stdarg.h"
#include "stdio.h"

void f(int n, ...) {
  va_list args;
  va_start(args, n);
  while (n--) {
    int x = va_arg(args, int);
    printf("%d ", x);
  }
  printf("\n");
  va_end(args);
}

int main(void) {
  f(2, 1, 2);
  f(3, 1, 2, 3);
  return 0;
}