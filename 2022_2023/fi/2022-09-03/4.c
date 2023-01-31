#include <ctype.h>
#include <stdio.h>

#define CMIN '0'
#define CMAX '9'
#define NDIG (CMAX - CMIN + 1)
#define LMIN 'A'

int minBase(char ns[]) {
  int i, n, b;

  for (i = 0; ns[i]; i++) {
    if (isdigit(ns[i]))
      n = ns[i] - CMIN;
    else
      n = ns[i] - LMIN + NDIG;
    b = (n > b ? n : b);
  }

  return b;
}

int main (int argc, char * argv[]) {
  if (argc == 2)
    printf("%d\n", minBase(argv[1]));
  return 0;
}
