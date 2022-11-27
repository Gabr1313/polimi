#include <stdio.h>
#define VAL_LEN 10
#define STOP 0

int main(int argc, char **argv) {
  float array[VAL_LEN], in;
  int i, dim;

  scanf("%f", &in);
  dim = 0;
  while (in != STOP) {
    if (dim < VAL_LEN) {
      array[dim] = in;
      dim++;
    }
    scanf("%f", &in);
  }

  for (i = 0; i < dim; i++) printf("%g ", array[i]);

  printf("\n");
  return 0;
}
