#include <stdio.h>

#define LEN_M 200

int compattaarray(int *, int);
int isPrime(int);

int main(int argc, char *argv[]) {
  int i, v[LEN_M], len, len2;

  do scanf("%d", &len);
  while (len <= 0 || len > LEN_M);

  for (i = 0; i < len; i++) scanf("%d", v + i);

  len2 = compattaarray(v, len);

  printf("\n");
  for (i = 0; i < len2; i++) printf("%d ", v[i]);
  printf("\n");

  return 0;
}

int compattaarray(int *v, int len) {
  int i, k;

  for (i = k = 0; i < len; i++)
    if (isPrime(*(v + i))) *(v + k++) = *(v + i);

  return k;
}

int isPrime(int n) {
  int p, i;
  p = (n < 4 ? n > 1 : n % 2 && n % 3);
  for (i = 5; p && i * i < n; i++) p = n % i && n % (i + 2);
  return p;
}
