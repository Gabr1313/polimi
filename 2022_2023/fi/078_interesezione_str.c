/*
Si scriva un sottoprogramma che ricevuti in ingresso 2 insiemi di caratteri
rappresentati con delle stringhe restituisca al chiamante l’insieme di caratteri (anche
esso rappresentato come una stringa) intersezione dei due insiemi in ingresso. Il
risultato conterrà tutti e i soli caratteri presenti in entrambe le stringhe, una sola
volta. Si assuma che negli insiemi di ingresso ogni carattere sia presente al più una
volta e che gli insiemi possano contenere solo caratteri minuscoli.

io lo faccio che conta anche i caratteri ripetuti
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NCHAR 256

char *intersezione(char[], char[]);

int main(int argc, char *argv[]) {
  char *ris;
  if (argc == 3) {
    if ((ris = intersezione(argv[1], argv[2]))) {
      printf("%s\n", ris);
      free(ris);
    }
  } else
    printf("Usage: %s string string\n", argv[0]);
  return 0;
}

char *intersezione(char a[], char b[]) {
  int map1[NCHAR], map2[NCHAR];
  int len, i;
  char *ris;

  memset(map1, 0, sizeof(int) * NCHAR);
  memset(map2, 0, sizeof(int) * NCHAR);

  for (i = 0; a[i]; ++i) ++map1[(int)a[i]];
  for (i = 0; b[i]; ++i) ++map2[(int)b[i]];
  len = 0;
  for (i = 0; i < NCHAR; ++i)
    if (map1[i] && map2[i]) ++len;
  ++len;

  if ((ris = malloc(sizeof(char) * (len)))) {
    len = 0;
    for (i = 0; i < NCHAR; ++i)
      if (map1[i] && map2[i]) ris[len++] = i;
    ris[len] = '\0';
  } else
    printf("Allocation problem of %d chars", len);

  return ris;
}
