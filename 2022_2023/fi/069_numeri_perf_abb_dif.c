/* Scrivere un programma in C (ANSI 89) che acquisita una stringa di al più 30 caratteri,
individui la sottostringa più lunga in essa contenuta, senza caratteri ripetuti. Il
programma visualizza la lunghezza di tale sottostringa, seguita da un carattere a-capo.
Realizzare la propria soluzione organizzandola in sottoprogrammi, come ritenuto più
opportuno.
## Esercizio 6 - Numeri perfetti, abbondanti e difettivi
Scrivere un programma in C (ANSI 89) che riceve in ingresso un array di 10 valori
numeri interi. Costruire un nuovo array
dove in corrispondenza di ogni elemento dell’array iniziale si mette:
+ 0 se l’elemento i è non strettamente positivo,
+ 1 se l’elemento i è un numero perfetto,
+ 2 se l’elemento i è abbondante,
+ 3 se l’elemento i è difettivo
Per definizione un numero è perfetto se corrisponde alla somma dei suoi divisori,
escluso se stesso; abbondante se è minore della somma dei suoi divisori, escluso se
stesso; altrimenti è difettivo.
Ad esempio: 6 e 28 sono perfetti, 12 e 18 sono abbondanti, mentre 8 e 10 sono
difettivi.
Il programma visualizza i valori inseriti, su una nuova riga la caratteristica del
numero, ed infine un istogramma verticale che rappresenta la quantità di numeri
perfetti, difettivi e abbondanti contenuti nell’array iniziale.
Realizzare la propria soluzione organizzandola in sottoprogrammi, come ritenuto più
opportuno.
Esempio:
input:
5 28 -1 0 6 10 18 -8 1 5
output:
5 28 -r 0 6 10 18 -8 1 5
3 1 0 0 1 3 2 0 3 3
*
*
* *
*** */

#include <stdio.h>
#define LEN 10
#define NTYPE 3
#define EMPTY ' '
#define FULL '*'

void populate(int[], int);
void find_type(int[], int[], int);
void view_arr(int[], int);
void view_istogramma(int[], int);
int somma_divisori(int);
int count_max(int[], int[], int, int);
void inizializza(int[], int);

int main(int argc, char* argv[]) {
  int array[LEN], type[LEN];

  populate(array, LEN);
  find_type(array, type, LEN);
  view_arr(array, LEN);
  view_arr(type, LEN);
  view_istogramma(type, LEN);

  return 0;
}

void populate(int array[], int len) {
  int i;

  for (i = 0; i < len; ++i) scanf("%d", &array[i]);
}

void find_type(int array[], int type[], int len) {
  int i, sum_div;

  for (i = 0; i < len; ++i) {
    if (array[i] <= 0)
      type[i] = 0;
    else {
      sum_div = somma_divisori(array[i]);
      if (sum_div == array[i])
        type[i] = 1;
      else if (sum_div > array[i])
        type[i] = 2;
      else
        type[i] = 3;
    }
  }
}

int somma_divisori(int num) {
  int i, ris;

  ris = -num;
  for (i = 1; i * i < num; i++)
    if (num % i == 0) ris += (i + num / i);

  return ris;
}

void view_arr(int array[], int len) {
  int i;
  for (i = 0; i < len; i++) printf("%d ", array[i]);
  printf("\n");
}

void view_istogramma(int type[], int len) {
  int i, count[NTYPE], max, j;

  max = count_max(type, count, len, NTYPE);

  printf("\n");
  for (i = max; i > 0; --i) {
    for (j = 0; j < NTYPE; j++)
      if (count[j] >= i)
        printf("%c", FULL);
      else
        printf("%c", EMPTY);
    printf("\n");
  }
}

int count_max(int type[], int count[], int len, int len_2) {
  int i, max;

  inizializza(count, len_2);
  max = 0;
  for (i = 0; i < len; i++)
    if (type[i]) {
      ++count[type[i] - 1];
      if (count[type[i] - 1] > max) max = count[type[i] - 1];
    }

  return max;
}

void inizializza(int array[], int len) {
  int i;

  for (i = 0; i < len; i++) array[i] = 0;
}
