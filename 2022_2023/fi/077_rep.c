/*
Scrivere un sottoprogramma rep che riceve in ingresso una stringa s e un intero n
(senz’altro non negativo). Il sottoprogramma restituisce una nuova stringa ottenuta
concatenando n copie di s.
ESEMPIO:
in: “esempio”, 3
out: “esempioesempioesempio”
in: “esempio”, 0						out: “ “
Non è consentito l’uso dei sottoprogrammi di libreria quali strcat, strcpy e simili.
Scrivere il programma che acquisisce da riga di comando la stringa s e l’intero n,
invoca il sottoprogramma sopra definito e visualizza il risultato.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *rep(char[], int);

int main(int argc, char *argv[]) {
  char *ris;
  int rip;
  if (argc == 3) {
    rip = atoi(argv[2]);
    if ((ris = rep(argv[1], rip))) {
      printf("%s\n", ris);
      free(ris);
    }
  } else
    printf("Usage: %s string number\n", argv[0]);
  return 0;
}

char *rep(char a[], int rip) {
  char *ris;
  int i, j, len;

  len = strlen(a);
  if ((ris = malloc(sizeof(char) * (rip * len + 1)))) {
    for (i = 0; i < rip; i++)
      for (j = 0; j < len; j++) *(ris + i * len + j) = a[j];
    *(ris + i * len + 1) = '\0';
  } else
    printf("Allocation error of %d char", (rip * len + 1));

  return ris;
}
