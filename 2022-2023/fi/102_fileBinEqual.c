#include <stdio.h>

#define DIM 1024

int diff(FILE *file1, FILE *file2) {
  int i, finished, areDiff, word1[DIM], word2[DIM], readed1, readed2;

  readed1 = fread(word1, sizeof(int), DIM, file1);
  readed2 = fread(word2, sizeof(int), DIM, file2);
  finished = 0;
  areDiff = 0;
  while (!areDiff && !finished) {
    if (readed1 == readed2) {
      for (i = 0; i < readed1 && !areDiff; i++)
        areDiff = !(word1[i] == word2[i]);
      if (!areDiff) {
        if (readed1 < DIM)
          finished = 1;
        else {
          readed1 = fread(word1, sizeof(int), DIM, file1);
          readed2 = fread(word2, sizeof(int), DIM, file2);
        }
      }
    } else
      areDiff = 1;
  }
  return areDiff;
}

int main(int argc, char **argv) {
  FILE *file1, *file2;
  if (argc == 3) {
    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");
    if (file1 && file2) {
      printf("%d\n", diff(file1, file2));
      fclose(file1);
      fclose(file2);
    }
  }
  return 0;
}
