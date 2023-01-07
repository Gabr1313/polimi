#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "tentativi.txt"
#define LEN 25
#define START 'a'
#define END 'z'
#define MAP_LEN (END - START + 1)
#define EQUAL '='
#define IN '+'
#define NOTIN 'X'

char *check(char[], char[]);

int main(int argc, char *argv[]) {
  char *ris, soluzione[LEN + 1], tentativo[LEN + 1];
  FILE *voc;

  scanf("%s", soluzione);
  voc = fopen(FILE_NAME, "r");
  if (voc) {
    ris = (char *)1;
    while (fscanf(voc, "%s", tentativo) == 1 && ris) {
      ris = check(tentativo, soluzione);
      if (ris) {
        printf("%s\n%s\n", tentativo, ris);
        free(ris);
      }
    }
  } else
    printf("File %s non esistente\n", FILE_NAME);

  return 0;
}

char *check(char tentativo[], char soluzione[]) {
  int i, len, pos, map[MAP_LEN];
  char *ris;

  memset(map, 0, sizeof(int) * MAP_LEN);
  for (i = 0; soluzione[i]; i++) map[soluzione[i] - START]++;
  len = i;

  ris = malloc(sizeof(char) * (len + 1));
  if (ris) {
    for (i = 0; i < len; i++)
      if (tentativo[i] == soluzione[i]) {
        ris[i] = EQUAL;
        map[ris[i] - START]--;
      }

    for (i = 0; i < len; i++)
      if (tentativo[i] != soluzione[i]) {
        pos = tentativo[i] - START;
        if (map[pos]) {
          ris[i] = IN;
          map[pos]--;
        } else
          ris[i] = NOTIN;
      }
    ris[i] = '\0';
  } else
    printf("check: problema allocazione dinamica\n");

  return ris;
}
