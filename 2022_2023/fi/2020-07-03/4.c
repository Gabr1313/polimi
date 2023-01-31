#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define LEN 30

int ometti(char src[], char dst[], char voc[]) {
  FILE *srcFile, *dstFile;
  char word[LEN + 1];
  int count, i, check;

  srcFile = fopen(src, "r");
  dstFile = fopen(dst, "w");
  if (srcFile && dstFile) {
    count = 0;
    while (fscanf(srcFile, "%s", word) == 1) {
      /* if (!strcmp(word, voc))
        count++;
      else
        fprintf(dstFile, "%s ", word); */

      check = 1;
      for (i = 0; check && word[i]; i++)
        check = (tolower(word[i]) == tolower(voc[i]));
      if (check)
        count++;
      else
        fprintf(dstFile, "%s ", word);
    }
    fclose(srcFile);
    fclose(dstFile);
  } else
    printf("ERRORE\n");

  return count;
}

int main(int argc, char* argv[]) {
  int ris;

  if (argc == 4) {
    ris = ometti(argv[1], argv[2], argv[3]);
    printf("%d\n", ris);
  } else
    printf("Uso: %s file file str\n", argv[0]);

  return 0;
}
