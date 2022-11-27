/*
Scrivere un sottoprogramma che ricevuto in ingresso un valore intero restituisce
al chiamante il numero di cifre che compaiono più di una volta. Per esempio, se il
sottoprogramma riceve in ingresso il valore 3282821 il sottoprogramma restituisce il
valore 2, perché la cifra 8 e 2 compaiono entrambe più di una volta.
 */

#include <stdio.h>
#define BASE 10

int contaDoppie(int);

int main(int argc, char *argv[]) {
  int num, ris;

  do scanf("%d", &num);
  while (num < 0);

  ris = contaDoppie(num);

  printf("%d\n", ris);
  return 0;
}

int contaDoppie(int num) {
  int doppie, cifra, i, contaRip[BASE];
  for (i = 0; i < BASE; i++) contaRip[i] = 0;

  doppie = 0;
  while (num > 0) {
    cifra = num % BASE;
    contaRip[cifra]++;
    if (contaRip[cifra] == 2) doppie++;
    num /= BASE;
  }

  return doppie;
}
