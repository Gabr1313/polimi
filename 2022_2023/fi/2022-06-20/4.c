#include <stdio.h>

#define LEN 35
#define SEP ' '

int compatibileParole(char schema[], char parola[]){
  int i, ris;

  ris = 1;
  for (i = 0; ris && schema[i] && parola [i]; i++){
    ris = !(schema[i] != SEP && schema[i] != parola[i]);
  }

  return !(schema[i] || parola[i] || !ris);
}


int compatibili (char schema[], FILE *fp){
  char parola[35];
  int ris;

  ris = 0;
  while (fscanf(fp, "%s", parola) == 1){
    ris += compatibileParole(schema, parola);
  }

  return ris;
}

#define STRING "d ta e"
#define FILE ".txt"

int main (void){
  printf("%d\n", compatibili(STRING, fopen(FILE, "r")));
  return 0;
}
