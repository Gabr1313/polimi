#include <stdio.h>

#define LEN 4
#define LENSTR 16

int main(void) {
  char c[LEN], tmp[LENSTR];
  double d[LEN];
  unsigned long int address0, addressA;
  int i;

  printf("CHAR\n\n");
  printf("Address of char 0: %p\n\n", c);
  sprintf(tmp, "%p", c);
  sscanf(tmp + 2, "%lx\n", &address0);
  for (i = 1; i < LEN; i++) {
    printf("Address of char %d: %p\n", i, c + i);
    printf("Difference (pointer %d - pointer 0) (hex): %d\n", i, i);
    sprintf(tmp, "%p", c + i);
    sscanf(tmp + 2, "%lx\n", &addressA);
    printf("Difference (address %d - address 0) (dec): %lu\n\n", i,
           addressA - address0);
  }
  printf("DOUBLE\n\n");
  printf("Address of double 0: %p\n\n", (void*)(d));
  sprintf(tmp, "%p\n", (void *)d);
  sscanf(tmp + 2, "%lx\n", &address0);
  for (i = 1; i < LEN; i++) {
    printf("Address of double %d: %p\n", i, (void *)(d + i));
    printf("Difference (pointer %d - pointer 0) (hex): %d\n", i, i);
    sprintf(tmp, "%p\n", (void *)(d + i));
    sscanf(&tmp[2], "%lx\n", &addressA);
    printf("Difference (address %d - address 0) (dec): %lu\n\n", i,
           addressA - address0);
  }

  return 0;
}
