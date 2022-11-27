#include <stdio.h>
#define SEC_IN_MIN 60
#define MIN_IN_ORA 60
#define ORA_IN_GIO 24

int main(int argc, char* argv[]) {
  int SEC_IN_ORA, SEC_IN_GIO, tempo, giorni, ore, minuti, secondi;
  /*oppure devo scriverle in minuscolo?*/

  SEC_IN_ORA = SEC_IN_MIN * MIN_IN_ORA;
  SEC_IN_GIO = SEC_IN_ORA * ORA_IN_GIO;

  scanf("%d", &tempo);

  giorni = tempo / SEC_IN_GIO;
  tempo = tempo % SEC_IN_GIO;

  ore = tempo / SEC_IN_ORA;
  tempo = tempo % SEC_IN_ORA;

  minuti = tempo / SEC_IN_MIN;

  secondi = tempo % SEC_IN_MIN;

  printf("%d %d %d %d\n", giorni, ore, minuti, secondi);
  return 0;
}
