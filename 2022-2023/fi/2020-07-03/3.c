#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE 10

int cifra(int n) {
  int i, map[BASE], cifra, ris;

  memset(map, 0, sizeof(int));
  n = abs(n);
  do {
    cifra = n % BASE;
    map[cifra]++;
    n /= BASE;
  } while (n > 0);

  /* ris = 0;
  for (i = 1; i < BASE; i++) {
    if (map[i] >= map[ris]) ris = i;
  } */

  ris = 0;
  for (i = 1; i < BASE; i++) {
    if (map[i] > map[ris])
      ris = i;
    else if (map[i] == map[ris] && ris % 2)
      ris = i;
  }

  return ris;
}

int main(int argc, char* argv[]) {
  if (argc == 2) {
    printf("%d\n", cifra(atoi(argv[1])));
  }
  return 0;
}
