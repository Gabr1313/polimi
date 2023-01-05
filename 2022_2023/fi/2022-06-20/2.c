#include <stdio.h>
#include <stdlib.h>

#define BASE 10

int monotono(int n, int* nCifre) {
  int digit, prev, ris;

  prev = n % BASE;
  n /= BASE;
  *nCifre = 1;
  ris = 1;
  while (n > 0) {
    digit = n % BASE;
    if (prev <= digit) ris = 0;
    prev = digit;
    n /= BASE;
    (*nCifre)++;
  }

  return ris;
}

int main(int argc, char* argv[]) {
  int nCifre, ris;
  if (argc == 2) {
    ris = monotono(atoi(argv[1]), &nCifre);
    printf("%d %d\n", ris, nCifre);
  } else {
    printf("Usage: %s word\n", argv[0]);
  }
  return 0;
}
