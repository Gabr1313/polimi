/*
Scrivere un sottoprogramma che riceve in ingresso un array di valori interi `v` e
qualsiasi altro parametro ritenuto necessario, ed altri due valori interi `da` e `a`.
Il sottoprogramma verifica se nell’array sono presenti tutti e soli i valori inclusi
nell’intervallo `[da,a]`, senza ripetizioni. In caso positivo il sottoprogramma
restituisce 1, 0 in caso contrario.
 */

#include <stdio.h>
#define MAX_LEN 256

int areAll(int[], int, int, int);

int main(int argc, char *argv[]) {
  int array[MAX_LEN], len, da, a, i, ris;

  do scanf("%d", &len);
  while (len < 1 || len > MAX_LEN);
  for (i = 0; i < len; i++) scanf("%d", &array[i]);
  scanf("%d", &da);
  scanf("%d", &a);

  ris = areAll(array, len, da, a);

  printf("%d\n", ris);
  return 0;
}

int areAll(int array[], int len, int a, int da) {
  int ris, i, map[MAX_LEN], lenMap, pos;

  /*
  lenMap = a - da + 1;
   */
  lenMap = a - da;
  if (lenMap < 0) lenMap = -lenMap;
  lenMap++;

  if (lenMap != len)
    ris = 0;
  else {
    for (i = 0; i < len; i++) map[i] = 0;
    ris = 1;
    for (i = 0; i < len && ris; i++) {
      pos = array[i] - a;
      if (pos >= len || pos < 0 || map[pos])
        ris = 0;
      else
        map[pos]++;
    }
  }
  return ris;
}
