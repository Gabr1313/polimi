#include <stdio.h>

int main(int argc, char* argv[]) {
  int num, max = 0, min = 0, cont, sum = 0, i = 0;
  float avg;
  printf("valore di controllo: ");
  scanf("%d", &cont);
  printf("ora inserisci la serie di valori:\n");
  scanf("%d", &num);
  while (num != cont) {
    if (i == 0) {
      max = num;
      min = num;
    } else {
      if (num > max)
        max = num;
      else if (num < min)
        min = num;
    }
    sum = sum + num;
    scanf("%d", &num);
    i++;
  }
  avg = (float)sum / i;
  printf("%d, %d, %g", min, max, avg);
}
