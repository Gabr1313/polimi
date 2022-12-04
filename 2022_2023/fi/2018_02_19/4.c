#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *rep(char[], int);

int main(int argc, char *argv[]) {
  char *s;
  if (argc == 3) {
    s = rep(argv[1], atoi(argv[2]));
    printf("%s\n", s);
    free(s);
  } else
    printf("Usage: %s string int\n", argv[0]);
  return 0;
}

char *rep(char s[], int val) {
  char *ris;
  int len, i, j, k;

  len = strlen(s);
  if ((ris = malloc((len * val + 1) * sizeof(char)))) {
    k = 0;
    for (i = 0; i < val; i++)
      for (j = 0; j < len; j++)
        ris[k++] = s[j];
    ris[k] = '\0';
  } else
    printf("Memory allocation problem\n");
  return ris;
}
