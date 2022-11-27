#include <stdio.h>

int main(int argc, char* argv[]) {
  float x;

  x = 0.0;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  x += 0.1;
  printf("%.23f ", x);
  if (x == 1.0)
    printf("uguale a 1.0\n");
  else
    printf("diverso da 1.0\n");
  return 0;
}