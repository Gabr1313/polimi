#include <stdio.h>
#include <stdlib.h>

#define NOME_FILE "parole.txt"
#define LEN 30

void analizza (char [], char *, int *);

int main (int argc, char * argv[]) {
  FILE * file;
  char word[LEN + 1], let;
  int nRip, max;

  file = fopen (NOME_FILE, "r");
  if (file) {
    max = 0;
    while (fscanf(file, "%s", word) == 1) {
      analizza(word, &let, &nRip);
      if (max < nRip)
        max = nRip;
      printf("%c %d\n", let, nRip);
    }
    printf("%d\n", max);
    fclose(file);
  } else
    printf("main: problemi apertura file %s\n", NOME_FILE);

  return 0;
}



void analizza (char word[], char * let, int * nRip) {
  int i, count;
  char min;

  min = word[0];
  count = 1;
  for (i = 1; word[i] != '\0'; i++)
    if (word[i] < min) {
       min = word[i];
       count = 1;
    } else if (word[i] == min)
       count++;

  *let = min;
  *nRip = count;
}


