#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LEN 25
#define FILENAME "dizionario.txt"

int angramma(char[], char[]);

int angramma(char s1[], char s2[]) {
  /* rigraziamo chatGPT */
  int counts1[26] = {0};
  int counts2[26] = {0};
  int i;
  if (strlen(s1) != strlen(s2)) {
    return 0;
  }
  for (i = 0; s1[i] != '\0'; i++) {
    counts1[s1[i] - 'a']++;
  }
  for (i = 0; s2[i] != '\0'; i++) {
    counts2[s2[i] - 'a']++;
  }
  for (i = 0; i < 26; i++) {
    if (counts1[i] != counts2[i]) {
      return 0;
    }
  }
  return 1;
}

int angrammaInt(char s1[], char s2[]) {
  int counts1[10] = {0};
  int counts2[10] = {0};
  int i;
  if (strlen(s1) != strlen(s2)) {
    return 0;
  }
  for (i = 0; s1[i] != '\0'; i++) {
    counts1[s1[i] - '0']++;
  }
  for (i = 0; s2[i] != '\0'; i++) {
    counts2[s2[i] - '0']++;
  }
  for (i = 0; i < 10; i++) {
    if (counts1[i] != counts2[i]) {
      return 0;
    }
  }
  return 1;
}

int dimmiAnagrammi(char voc[]) {
  FILE *dizionario;
  int count;
  char word[MAX_LEN + 1];

  dizionario = fopen(FILENAME, "r");
  if (dizionario) {
    count = 0;
    while (fscanf(dizionario, "%s", word) == 1) {
      if (angramma(word, voc)) count++;
    }
  } else
    count = -1;
  fclose(dizionario);
  return count;
}

int dimmiAnagrammiInt(int num) {
  FILE *dizionario;
  int count;
  char word[MAX_LEN + 1], numberStr[MAX_LEN + 1];

  dizionario = fopen(FILENAME, "r");
  if (dizionario) {
    sprintf(numberStr, "%d", num);
    count = 0;
    while (fscanf(dizionario, "%s", word) == 1) {
      if (angrammaInt(word, numberStr)) count++;
    }
  } else
    count = -1;
  fclose(dizionario);
  return count;
}

int main (int argc, char * argv[]){
  if (argc == 2){
    printf("%d\n",dimmiAnagrammiInt(atoi(argv[1])));
  } else {
    printf("Usage: %s word\n", argv[0]);
  }
  return 0;
}

