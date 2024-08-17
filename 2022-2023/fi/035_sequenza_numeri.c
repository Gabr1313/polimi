#include <stdio.h>
#define MAX 100
#define INIZIO '0'
#define FINE '9'
int main(int argc, char *argv[]) {
  char frase[MAX + 1];
  int count, min, max, i;

  gets(frase);

  i = 0;
  while (frase[i] != '\0' && frase[i] < INIZIO || frase[i] > FINE) i++;
  if (frase[i] == '\0')
    printf("No number found");
  else {
    count = 0;
    while (frase[i + count] >= INIZIO && frase[i + count] <= FINE) count++;
    min = count;
    max = count;

    for (i = 0; frase[i] != '\0'; i++) {
      count = 0;
      while (frase[i + count] >= INIZIO && frase[i + count] <= FINE) count++;
      if (count)
        if (count > max)
          max = count;
        else if (count < min)
          min = count;
      i += count;
    }

    printf("%d %d\n", min, max);
  }
  return 0;
}
