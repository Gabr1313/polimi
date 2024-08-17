#include <stdio.h>
#include <string.h>
#define DIM 100
#define DIM_C 5

int main(int argc, char *argv[]) {
  char frase[DIM + 1], sym[DIM_C + 1];
  int i, j, count, found;

  gets(sym);
  gets(frase);

  count = 0;
  for (i = 0; frase[i] != '\0'; i++) {
    found = 0;
    for (j = 0; sym[j] != '\0' && !found; j++)
      if (frase[i] == sym[j]) {
        found = 1;
        count++;
      }
  }

  printf("%d\n", count);
  return 0;
}
