#include <ctype.h>
#include <stdio.h>

#define RIGHT "OK"
#define WRONG "KO"
#define VOC 'V'
#define CON 'C'
#define DIG 'D'
#define VOCS "aeiou"

int check(char[], char[]);
int isVoc(char);

int main(int argc, char* argv[]) {
  if (argc == 3)
    if (check(argv[1], argv[2]))
      printf("%s\n", RIGHT);
    else
      printf("%s\n", WRONG);
  else
    printf("Uso: %s string string\n", argv[0]);

  return 0;
}

int check(char stin[], char formato[]) {
  int i, ris;

  ris = 1;
  for (i = 0; ris && stin[i] && formato[i]; i++) switch (formato[i]) {
      case VOC:
        ris = isVoc(stin[i]);
        break;
      case CON:
        ris = isalpha(stin[i]) && !isVoc(stin[i]);
        break;
      case DIG:
        ris = isdigit(stin[i]);
        break;
      default:
        ris = 0;
    }

  return ris && !formato[i] && !stin[i];
}

int isVoc(char c) {
  int i, ris;

  c = tolower(c);
  for (i = ris = 0; !ris && VOCS[i]; i++) ris = (VOCS[i] == c);

  return ris;
}
