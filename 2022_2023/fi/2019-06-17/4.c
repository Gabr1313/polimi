#include <stdio.h>

#define LEN 30
#define OUT "primi.txt"

void cntPrimes(FILE *, FILE *);
int primesBefore(int);
int isPrimeS(int);

/* int main(int argc, char *argv[]) {
  char fileName[LEN + 1];
  FILE *fileIn, *fileOut;

  scanf("%s", fileName);
  fileIn = fopen(fileName, "r");
  if (fileIn) {
    fileOut = fopen(OUT, "w");
    if (fileOut) {
      cntPrimes(fileIn, fileOut);
      fclose(fileOut);
    } else
      printf("File %s non apribile", OUT);
    fclose(fileIn);
  } else
    printf("File %s non apribile", fileName);

  return 0;
} */

int main(int argc, char *argv[]) {
  FILE *fileIn, *fileOut;

  if (argc == 3) {
    fileIn = fopen(argv[1], "r");
    if (fileIn) {
      fileOut = fopen(argv[2], "w");
      if (fileOut) {
        cntPrimes(fileIn, fileOut);
        fclose(fileOut);
      } else
        printf("File %s non apribile", argv[2]);
      fclose(fileIn);
    } else
      printf("File %s non apribile", argv[1]);
  }

  return 0;
}

void cntPrimes(FILE *in, FILE *out) {
  int n, cnt;

  while (fscanf(in, "%d", &n) == 1) {
    cnt = primesBefore(n);
    fprintf(out, "%d %d\n", n, cnt);
  }
}

int primesBefore(int n) {
  int d, cnt;

  if (n < 2) cnt = 0;
  if (n == 2)
    cnt = 1;
  else {
    cnt = 2;
    for (d = 5; d <= n; d += 2) cnt += isPrimeS(d);
  }

  return cnt;
}

int isPrimeS(int n) {
  int i, p;
  p = n % 3;
  for (i = 5; p && i * i <= n; i += 6) p = n % i && n % i + 2;
  return !!p;
}
