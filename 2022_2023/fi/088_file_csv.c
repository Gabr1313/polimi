/* Scrivere un programma in C (ANSI 89) che acquisisce una sequenza di valori di lunghezza
a priori ignota dall’utente, che si ritiene terminata quando l’utente inserisce un
valore inferiore a 1. Il programma salva i numeri primi nel file primi.csv, scrivendoli
uno per riga.
Per esempio, se l’utente in ingresso fornisce i valori 4 5 1 2 8 20 17 42 12 9 5 -12 il
contenuto del file creato sarà:
5
2
17
5 */

#include <stdio.h>

int is_prime(int);

int main(int argc, char *argv[]) {
  int val;
  FILE *out;
  if ((out = fopen("primi.csv", "w"))) {
    scanf("%d", &val);
    while (val > 1) {
      if (is_prime(val)) fprintf(out, "%d\n", val);
      scanf("%d", &val);
    }
    fclose(out);
  } else
    printf("Error managing the file");
  return 0;
}

int is_prime(int val) {
  int div;
  if (val < 1) return 0;
  if (val == 1 || val == 2) return 1;
  if (val & 1) { /* se e' dispari */
    for (div = 3; div * div < val; div += 2)
      if (!(val % div)) return 0;
    return 1;
  }
  return 0;
}
