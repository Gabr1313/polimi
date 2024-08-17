#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LEN 30

int ometti(char[], char[], char[]);
int omettiTutti(char[], char[], char[]);

int main(int argc, char *argv[]) {
  if (argc == 4) /* ometti(argv[1], argv[2], argv[3]); */
    omettiTutti(argv[1], argv[2], argv[3]);
  else
    printf("Usage: %s src dst word\n", argv[0]);
  return 0;
}

int ometti(char nomeFile1[], char nomeFile2[], char wordToDelete[]) {
  int count, alpha;
  char word[LEN + 1];
  FILE *input, *output;
  input = fopen(nomeFile1, "r");
  output = fopen(nomeFile2, "w");
  if (input && output) {
    count = 0;
    while (fscanf(input, "%s", word) == 1) {
      alpha = getc(input);
      if (strcmp(word, wordToDelete)) {
        fprintf(output, "%s", word);
        if (alpha != EOF) fprintf(output, "%c", alpha);
      } else {
        count++;
        if (alpha == '\n') fprintf(output, "%c", alpha);
      }
    }
  } else {
    printf("ERRORE\n");
    count = -1;
  }
  return count;
}

int strcmpAbs(char word1[], char word2[]) {
  int i, diff;
  diff = 0;
  for (i = 0; word1[i] && word2[i] && diff == 0; i++) {
    diff = toupper(word1[i]) - toupper(word2[i]);
  }
  if ((word1[i] != '\0' && word2[i] == '\0') ||
      (word1[i] == '\0' && word2[i] != '\0'))
    diff = toupper(word1[i]) - toupper(word2[i]);
  return diff;
}

int omettiTutti(char nomeFile1[], char nomeFile2[], char wordToDelete[]) {
  int count, alpha;
  char word[LEN + 1];
  FILE *input, *output;
  input = fopen(nomeFile1, "r");
  output = fopen(nomeFile2, "w");
  if (input && output) {
    count = 0;
    while (fscanf(input, "%s", word) == 1) {
      alpha = getc(input);
      if (strcmp(word, wordToDelete)) {
        fprintf(output, "%s", word);
        if (alpha != EOF) fprintf(output, "%c", alpha);
      } else {
        count++;
        if (alpha == '\n') fprintf(output, "%c", alpha);
      }
    }
  } else {
    printf("ERRORE\n");
    count = -1;
  }
  return count;
}
