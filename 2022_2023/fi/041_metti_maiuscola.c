#include <stdio.h>

#define MAX_LEN 512
#define INIZIO 'a'
#define FINE 'z'
#define DIFF 'A' - 'a'
#define SEP ' '

void metti_maiuscole(char[]);

int main(int argc, char *argv[]) {
  char frase[MAX_LEN];

  gets(frase);

  metti_maiuscole(frase);

  puts(frase);
  return 0;
}

void metti_maiuscole(char frase[]) {
  int i;

  if (frase[0] >= INIZIO && frase[0] <= FINE) frase[0] += DIFF;
  for (i = 1; frase[i] != '\0'; i++)
    if (frase[i - 1] == SEP) {
      if (frase[i] >= INIZIO && frase[i] <= FINE) frase[i] += DIFF;
    } else if (frase[i] >= INIZIO + DIFF && frase[i] <= FINE + DIFF)
      frase[i] -= DIFF;
}
