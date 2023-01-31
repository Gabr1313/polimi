#include <math.h>
#include <stdio.h>
#include <string.h>

#define BASE 10

int isnarc(int, int);

void narc(int* n, int* t, int len, int x) {
  int i;

  for (i = 0; i < len; i++) *(t + i) = isnarc(*(n + i), x);
}

int isnarc(int n, int x) {
  int d, sum, t;

  sum = 0;
  t = n;
  while (t > 0 && sum < n) {
    d = t % BASE;
    sum += pow(d, x);
    t /= BASE;
  }

  return !t && sum == n;
}

#define LEN 100

int main(void) {
  int len, i, x, n[LEN], t[LEN];

  scanf("%d", &x);
  do scanf("%d", &len);
  while (len <= 0 || len > LEN);

  for (i = 0; i < len; i++) scanf("%d", n + i);
  memset(t, 0, sizeof(int) * len);

  narc(n, t, len, x);

  for (i = 0; i < len; i++) printf("%5d %2d\n", *(n + i), *(t + i));

  return 0;
}
