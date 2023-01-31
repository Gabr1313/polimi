#include <ctype.h>
#include <stdio.h>

#define SPACE ' '

int eliminaInterpunzione(char frase[]) {
  int i, j;
  for (i = 0, j = 0; frase[i]; i++)
    if (isalnum(frase[i]) || frase[i] == SPACE)
      frase[i - j] = frase[i];
    else
      j++;
  frase[i - j] = '\0';

  return j;
}

#define LEN 200

int main(void) {
  int ris;
  char frase[LEN + 1];

  fgets(frase, LEN + 1, stdin);
  ris = eliminaInterpunzione(frase);
  printf("%s\n%d\n", frase, ris);

  return 0;
}
