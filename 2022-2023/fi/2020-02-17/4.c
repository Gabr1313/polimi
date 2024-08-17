#include <stdio.h>

#define LEN 40
#define MAX 200
#define SEP '.'
#define SPACE ' '
#define SPACE2 '\n'

void analizza(FILE *, int *, int *, int *, int *);

int main(int argc, char *argv[]) {
  char nomeFile[LEN + 1];
  FILE *file;
  int max, min, righe, frasi;

  scanf("%s", nomeFile);
  file = fopen(nomeFile, "r");
  if (file) {
    analizza(file, &max, &min, &righe, &frasi);
    fclose(file);
    printf("max: %d\n", max);
    printf("min: %d\n", min);
    printf("righe: %d\n", righe);
    printf("frasi: %d\n", frasi);
  } else
    printf("ERRORE\n");

  return 0;
}

void analizza(FILE *file, int *max_p, int *min_p, int *righe_p, int *frase_p) {
  char riga[MAX + 1], *check;
  int i, c;

  *righe_p = *frase_p = *min_p = *max_p = 0;
  if ((check = fgets(riga, MAX + 1, file))) {
    *righe_p = 1;
    for (i = 0, c = 0; riga[i]; i++) {
      if (riga[i] != SPACE && riga[i] != SPACE2) c++;
      if (riga[i] == SEP) (*frase_p)++;
    }
    *max_p = *min_p = c;
  }

  while ((check = fgets(riga, MAX + 1, file))) {
    (*righe_p)++;
    for (i = 0, c = 0; riga[i]; i++) {
      if (riga[i] != SPACE && riga[i] != SPACE2) c++;
      if (riga[i] == SEP) (*frase_p)++;
    }
    if (*max_p < c)
      *max_p = c;
    else if (*min_p > c)
      *min_p = c;
  }
}
