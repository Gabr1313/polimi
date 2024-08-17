/*
Quesito 2 (6 punti) Punteggio ottenuto: . . . /6
Scrivere un sottoprogramma che ricevuto in ingresso un array monodimensionale e
qualsiasi parametro ritenuto strettamente necessario calcola e trasmette al
chiamante l’elemento della sottosequenza di elementi adiacenti uguali tra loro
piu lunga e la sua lunghezza. ` Esempio: Ingresso: 128337466663228888833 Uscita:
elemento: 8 lunghezza sottosequenza: 5
 */

#include <stdio.h>
#define MAX_LEN 21
/*
1 2 8 3 3 7 4 6 6 6 6 3 2 2 8 8 8 8 8 3 3
 */
void contaRip(int[], int, int *, int *);

int main(int argc, char *argv[]) {
  int array[MAX_LEN], dim, elem, sott;

  for (dim = 0; dim < MAX_LEN; dim++) scanf("%d", &array[dim]);

  contaRip(array, dim, &elem, &sott);

  printf("%d %d\n", elem, sott);
  return 0;
}

void contaRip(int array[], int dim, int *elem, int *sott) {
  int i, elemPr, sottPr;

  *elem = array[0];
  elemPr = array[0];
  *sott = 1;
  sottPr = 1;
  for (i = 1; i < dim; i++) {
    if (array[i] == elemPr) {
      sottPr++;
      if (sottPr > *sott) {
        *sott = sottPr;
        *elem = elemPr;
      }
    } else {
      elemPr = array[i];
      sottPr = 1;
    }
  }
}
