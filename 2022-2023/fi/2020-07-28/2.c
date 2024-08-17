#include <ctype.h>
#include <stdio.h>

#define LEN 8

int verifica(char[]);

int main(int argc, char* argv[]) {
  int ris;

  if (argc == 2) {
    ris = verifica(argv[1]);
    printf("%d\n", ris);
  } else
    printf("Uso: %s str\n", argv[0]);

  return 0;
}

int verifica(char psw[]) {
  int dig, car, i, eq, ris;

  if (psw[0] && psw[1]) {
    dig = (isdigit(psw[0]) || isdigit(psw[1]));
    car = (!isalnum(psw[0]) || !isalnum(psw[1]));
    eq = 0;
    for (i = 2; psw[i] && !eq; i++) {
      dig = dig || isdigit(psw[i]);
      car = car || !isalnum(psw[i]);
      eq = eq || (psw[i] == psw[i - 1] && psw[i] == psw[i - 2]);
    }
    ris = (i >= LEN && dig && car && !eq);
  } else
    ris = 0;

  return ris;
}
