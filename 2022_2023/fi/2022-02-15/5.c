#include <stdio.h>
#include <stdlib.h>

#define BASE 10

int genera (int c0, int c1, int dim){
  int digit, ris, mul;

  if (dim >= 3) {
    ris = c1 * BASE + c0;
    dim -= 2;
    mul = BASE * BASE;
    do {
      digit = abs (c0 - c1);
      ris += digit * mul;
      mul *= BASE;
      dim--;
      c0 = c1;
      c1 = digit;
    } while (dim > 0);
  } else
    ris = -1;

  return ris;
}

int main (int argc, char * argv[]){
  int ris;
  if (argc == 4){
    ris = genera(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
    printf("%d\n", ris);
  }
  return 0;
}
