#include <stdio.h>
#include <stdlib.h>

int gcdExtended(int a, int b, int *x, int *y);

int modInverse(int b, int m) {
  int x, y;
  int g = gcdExtended(b, m, &x, &y);
  if (g != 1) return -1;
  return (x % m + m) % m;
}

int gcdExtended(int a, int b, int *x, int *y) {
  int x1, y1, gcd;
  if (a == 0) {
    *x = 0, *y = 1;
    return b;
  }
  gcd = gcdExtended(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}

int main(int argc, char *argv[]) {
  int check;
  if (argc == 3) {
    check = modInverse(atoi(argv[1]), atoi(argv[2]));
    if (check != -1)
      printf("%d\n", check);
    else
      printf("%d and %d are not coprime\n", atoi(argv[1]), atoi(argv[2]));

  } else
    printf("Usage: %s a b c\n""i.e. a / b mod c\n", argv[0]);
  return 0;
}
