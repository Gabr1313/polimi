#include <stdio.h>
#include <stdlib.h>

int tuttiSoli(int v[], int len, int da, int a) {
  int i, ris, len2;
  int* check;

  len2 = a - da + 1;
  ris = 0;
  if (len2 == len) {
    check = calloc(sizeof(int), (len2));
    if (check) {
      ris = 1;
      for (i = 0; i < len && ris; i++)
        if (v[i] < da || v[i] > a)
          ris = 0;
        else {
          if (check[i])
            ris = 0;
          else
            check[i] = 1;
        }
      free(check);
    } else
      printf("tuttiSoli: problema allocazione dinamica\n");
  }

  return ris;
}

#define LEN 5

int main(void) {
  int v[LEN], i, da, a;

  scanf("%d %d", &da, &a);
  for (i = 0; i < LEN; i++) scanf("%d", &v[i]);

  printf("%d\n", tuttiSoli(v, LEN, da, a));

  return 0;
}
