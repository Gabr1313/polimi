/*
Scrivere un sottoprogramma baricentro che ricevuto in ingresso un array di valori
interi e qualsiasi altro parametro ritenuto strettamente necessario restituisce
l’indice dell’elemento che fa da baricentro agli elementi dell’array, -1 se non esiste.
Definiamo baricentro di un array di h elementi, l’elemento in posizione i tale per cui:
`v[0] + v[1] + ... + v[i] = v[i + 1] + v[i + 2] + ... + v[h - 1]`
Se dovessero esserci più baricentri, il sottoprogramma restituirebbe quello più a
sinistra.
ESEMPIO:
in: 1 0 5 10 4 4 2 6 0 0
out: 3
La somma dei primi 4 elementi è uguale a 16 come quella degli ultimi 6 elementi
in: 1 0 5 10 4 4 2 7 0 0
out: -1
 */

/* essendoci in input degli interi, questi possono anche essere negativi.
 * trovaBaricentro() restituisce i, e non i - 1, altrimenti il caso in cui il baricentro
 * fosse prima del primo numero (in i = 0), il risultato sarebbe ambiguo
 */

#include <stdio.h>
#define LEN_MAX 100

int trovaBaricentro(int[], int);

int main(int argc, char *argv[]) {
  int array[LEN_MAX], len, i, ris;

  do scanf("%d", &len);
  while (len < 0 || len > LEN_MAX);
  for (i = 0; i < len; i++) scanf("%d", &array[i]);

  ris = trovaBaricentro(array, len);

  printf("%d\n", ris);
  return 0;
}

int trovaBaricentro(int array[], int len) {
  int sommaTot, sommaI, sommaF, i;

  sommaTot = 0;
  for (i = 0; i < len; i++) sommaTot += array[i];

  sommaI = 0;
  sommaF = sommaTot;
  for (i = 0; i < len && sommaI != sommaF; i++) {
    sommaI += array[i];
    sommaF -= array[i];
  }

  if (i == len) return -1;
  return i;
}
