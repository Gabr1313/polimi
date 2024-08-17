#include <stdio.h>
#include <stdlib.h>

#define BASE 10

int monotono(int n, int* nCifre) {
  int cifra, cifraPrec, ris, count;

  cifraPrec = n % BASE;
  n /= BASE;
  count = 1;
  *nCifre = 1;
  ris = 1;

  while (n > 0) {
    (*nCifre)++;
    count++;
    cifra = n % BASE;
    if (cifra <= cifraPrec) ris = 0;
    cifraPrec = cifra;
    n /= BASE;
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
