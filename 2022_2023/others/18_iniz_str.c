#include <stdio.h>

int main() {
  char *mesi[] = {"gennaio", "febbraio", "marzo"};
  /* non funziona! e' come se le quadre indicano di riservare anche la memoria, altrimenti no
  char **mesi = {"gennaio", "febbraio", "marzo"}; */
  printf("%s\n", mesi[2]);

  return 0;
}
