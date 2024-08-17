#include <stdio.h>

int main(int argc, char* argv[]) {
  int num1, num2, i, j, k, u, v, ris, tmp;
  scanf("%d", &num1);
  scanf("%d", &num2);

  if (num1 == 0)
    ris = num2;
  else if (num2 == 0)
    ris = num1;
  else {
    u = num1;
    v = num2;

    i = 0;
    while (u % 2 == 0) {
      u = u / 2; /* u = u >> 1; */
      i++;
    }
    j = 0;
    while (v % 2 == 0) {
      v /= 2;
      j++;
    }

    if (i < j)
      k = i;
    else
      k = j;

    while (v) {
      if (u > v) {
        tmp = u;
        u = v;
        v = tmp;
      }

      v -= u;

      if (v)
        while (v % 2 == 0) v /= 2;
    }

    while (k > 0) { /* u = u << k; */
      u *= 2;
      k--;
    }

    ris = u;
  }

  printf("%d\n", ris);
  return 0;
}
