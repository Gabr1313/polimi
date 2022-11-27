#include <stdio.h>
#define GR_MAX 8

int main(int argc, char *argv[]) {
  int pol1[GR_MAX], pol2[GR_MAX], polProd[GR_MAX * 2], i, j, h, gr1, gr2, grProd;

  do scanf("%d", &gr1);
  while (gr1 < 0 || gr1 > GR_MAX);
  do scanf("%d", &gr2);
  while (gr2 < 0 || gr2 > GR_MAX);
  for (i = 0; i < gr1; i++) scanf("%d", &pol1[i]);
  for (i = 0; i < gr2; i++) scanf("%d", &pol2[i]);

  grProd = gr1 + gr2 - 1;
  for (i = 0; i < grProd; i++) {
    polProd[i] = 0;
    for (j = 0; j < gr1 && j < grProd; j++) {
      h = i - j;
      if (h >= 0 && h < gr2) polProd[i] += pol1[j] * pol2[h];
    }
  }

  for (i = 0; i < grProd; i++) printf("%d ", polProd[i]);
  printf("\n");
  return 0;
}
