#include <stdio.h>

#define LEN 4
#define LENSTR 16

int main(void) {
  char c[LEN], tmp[LENSTR];
  double d[LEN];
  unsigned long int address0, addressA;
  int i;

  printf("CHAR\n\n");
  printf("Address of char 0: %p\n\n", (void *)&c[0]);
  sprintf(tmp, "%p\n", (void *)&c[0]);
  sscanf(&tmp[2], "%lx\n", &address0);
  for (i = 1; i < LEN; i++) {
    printf("Address of char %d: %p\n", i, (void *)&c[i]);
    printf("Difference (pointer %d - pointer 0) (hex): %p\n", i,
           (void *)(&c[i] - &c[0]));
    sprintf(tmp, "%p\n", (void *)&c[i]);
    sscanf(&tmp[2], "%lx\n", &addressA);
    printf("Difference (address %d - address 0) (dec): %lu\n\n", i,
           addressA - address0);
  }
  printf("DOUBLE\n\n");
  printf("Address of double 0: %p\n\n", (void *)&d[0]);
  sprintf(tmp, "%p\n", (void *)&d[0]);
  sscanf(&tmp[2], "%lx\n", &address0);
  for (i = 1; i < LEN; i++) {
    printf("Address of double %d: %p\n", i, (void *)&d[i]);
    printf("Difference (pointer %d - pointer 0) (hex): %p\n", i,
           (void *)(&d[i] - &d[0]));
    sprintf(tmp, "%p\n", (void *)&d[i]);
    sscanf(&tmp[2], "%lx\n", &addressA);
    printf("Difference (address %d - address 0) (dec): %lu\n\n", i,
           addressA - address0);
  }

  return 0;
}
