#include <stdio.h>

void stampa_divisori(FILE *, int);

int main(int argc, char *argv[]) {
  int val, ris;
  FILE *out;

  if ((out = fopen("ris.txt", "w"))) {
    ris = 0;
    scanf("%d", &val);
    while (val > 0) {
      ris++;
      stampa_divisori(out, val);
      scanf("%d", &val);
    }

    printf("%d\n", ris);
  } else
    printf("Can't open the file.\n");
  return 0;
}

void stampa_divisori(FILE *out, int val) {
  int i, tot;

  tot = 0;
  for (i = 2; i * i < val; i++)
    if (val % i == 0)
      tot += 2;
  if (i * i == val)
    tot ++;

  fprintf(out, "%d %d\n", val, tot);
}

