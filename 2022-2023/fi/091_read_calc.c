/* Scrivere un programma in C (ANSI 89) che chiede all’utente il nome di un file (stringa
di al più 40 caratteri) di testo contenente valori interi. Il programma calcola e
visualizza le seguenti informazioni:
+ numero di valori presenti nel file
+ valore massimo
+ valore minimo
+ numero di valori positivi
+ numero di valori negativi
+ numero di valori nulli
+ avg dei valori presenti
Nel caso in cui il file sia vuoto, viene visualizzato il messaggio File vuoto */

#include <stdio.h>
#define MAX_LEN (40)

int main(int argc, char *argv[]) {
  char nomefile[MAX_LEN + 1];
  FILE *in;
  int check, sum, tot, max, min, pos, neg, nul, val;
  float avg;

  scanf("%s", nomefile);
  if ((in = fopen(nomefile, "r"))) {
    check = fscanf(in, "%d", &val);
    if (check > 0) {
      tot = 1;
      sum = val;
      max = val;
      min = val;
      pos = (max > 0);
      neg = (max < 0);
      nul = (max == 0);
      check = fscanf(in, "%d", &val);
      while (check > 0) {
        tot++;
        sum += val;
        if (max < val)
          max = val;
        else if (min > val)
          min = val;
        if (val > 0)
          pos++;
        else if (val < 0)
          neg++;
        else
          nul++;
        check = fscanf(in, "%d", &val);
      }
      avg = (float)sum / tot;

      printf("tot = %d\n", tot);
      printf("max = %d\n", max);
      printf("min = %d\n", min);
      printf("pos = %d\n", pos);
      printf("neg = %d\n", neg);
      printf("nul = %d\n", nul);
      printf("avg = %g\n", avg);
    } else
      printf("Empty file\n");

  } else
    printf("No file called %s found.\n", nomefile);
  return 0;
}
