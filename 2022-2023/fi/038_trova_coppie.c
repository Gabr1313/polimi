#include <stdio.h>
#define LEN 10

int main(int argc, char *argv[]) {
  int lista[LEN], i, j, count;

  for (i = 0; i < LEN; i++) scanf("%d", &lista[i]);

  count = 0;
  for (i = 0; i < LEN - 1; i++)
    for (j = i + 1; j < LEN; j++)
      if (lista[i] == lista[j]) count++;

  printf("%d", count);
  return 0;
}
