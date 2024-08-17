/* Scrivere un programma in C (ANSI 89) che acquisisce una sequenza di al più 20 valori
interi, chiedendo all’utente inizialmente quanti valori vorrà fornire, num.
Il programma acquisisce num valori e memorizza in una opportuna struttura dati la
sequenza di valori i cui elementi sono strettamente crescenti, trascurando i valori che
risultano non essere ordinati. Al termine dell’acquisizione il programma visualizza la
lunghezza della sequenza, seguita, su una nuova riga, dalla sequenza stessa.
L’utente inserirà sempre un numero di valori coerente con la richiesta.
Avvalersi di due sottoprogrammi: fillarrord e viewarr: il primo acquisisce i dati e
memorizza i dati ritenuti validi, il secondo visualizza il contenuto di un array.
Esempio:
input:
1 1 6 2 5 7
contenuto dell’array: 1 6 7 */

#include <stdio.h>
#define LEN_MAX 20

int fill_arr_ord(int[], int);
void view_arr(int[], int);

int main(int argc, char* argv[]) {
  int array[LEN_MAX], len, len_2;

  scanf("%d", &len);
  len_2 = fill_arr_ord(array, len);

  printf("%d\n", len_2);
  view_arr(array, len_2);

  return 0;
}

int fill_arr_ord(int array[], int len) {
  int i, val, len_2;

  scanf("%d", &array[0]);
  len_2 = 1;
  for (i = 1; i < len; i++) {
    scanf("%d", &val);
    if (val > array[len_2]) {
      array[len_2] = val;
      ++len_2;
    }
  }

  return len_2;
}

void view_arr(int array[], int len) {
  int i;

  for (i = 0; i < len; i++) printf("%d ", array[i]);
  printf("\n");
}
