#include <stdio.h>
#define MIN 1
#define MAX 16
#define ARIA_CENTRO 2
#define BLOCCHI '#'
#define ARIA ' '

int main(int argc, char *argv[]) {
  int piani, i, j, nAria, nBlocchi;
  do scanf("%d", &piani);
  while (piani < MIN || piani > MAX);

  for (i = 1; i <= piani; i++) {
    nAria = piani - i;
    nBlocchi = piani - nAria;
    for (j = 0; j < nAria; j++) printf("%c", ARIA);
    for (j = 0; j < nBlocchi; j++) printf("%c", BLOCCHI);
    for (j = 0; j < ARIA_CENTRO; j++) printf("%c", ARIA);
    for (j = 0; j < nBlocchi; j++) printf("%c", BLOCCHI);
    printf("\n");
  }

  return 0;
}
