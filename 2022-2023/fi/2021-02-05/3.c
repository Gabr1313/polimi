#include <stdio.h>
#include <stdlib.h>

float *distanzaLineare(float start, float stop, int num, int escludiStop) {
  int i;
  float *ris, step;

  ris = malloc(sizeof(float) * num);
  if (ris) {
    step = (stop - start) / (num - !escludiStop);
    printf("%f", step);
    ris[0] = start;
    for (i = 1; i < num; i++) ris[i] = ris[i - 1] + step;
  } else
    printf("distanzaLineare: Problema allocazione dinamica\n");

  return ris;
}

int main(int argc, char *argv[]) {
  int i;
  float *arr;

  if (argc == 5) {
    arr = distanzaLineare(atof(argv[1]), atof(argv[2]), atoi(argv[3]),
                          atoi(argv[4]));
    for (i = 0; i < atoi(argv[3]); i++) printf("%g\n", arr[i]);
    free(arr);
  }

  return 0;
}
