#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10

int countRip(int n) {
  int d, v[BASE], c;

  n = (n > 0 ? n : -n);
  memset(v, 0, sizeof(int) * BASE);
  c = 0;
  while (n > 0 && c < BASE) {
    d = n % BASE;
    c += (++v[d] == 2);
    n /= BASE;
  }

  return c;
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    printf("%d\n", countRip(atoi(argv[1])));
  }
  return 0;
}
