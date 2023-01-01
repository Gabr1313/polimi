#include <stdio.h>
#include <string.h>

#define MAX_LEN 25
#define FILENAME "dizionario.txt"

int angramma(char s1[], char s2[]);

int dimmiAnagrammi(char voc[]){
  FILE * dizionario;
  int count;
  char word[MAX_LEN + 1];

  dizionario = fopen (FILENAME, "r");
  if (dizionario){
    count = 0;
    while (fscanf(dizionario, "%s", word) == 1){
      if (angramma(word, voc))
        count++;
    }
  } else
    count = -1;
  fclose(dizionario);
  return count;
}

int dimmiAnagrammiInt(int num){
  FILE * dizionario;
  int count;
  char word[MAX_LEN + 1], numberStr[MAX_LEN + 1];

  dizionario = fopen (FILENAME, "r");
  if (dizionario){
    sprintf(numberStr, "%d", num);
    count = 0;
    while (fscanf(dizionario, "%s", word) == 1){
      if (angramma(word, numberStr))
        count++;
    }
  } else
    count = -1;
  fclose(dizionario);
  return count;
}
