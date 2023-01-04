#include <stdio.h>
#include <string.h>

#define MIN 0
#define MAX 199
#define LEN (MAX - MIN + 1)

int fMaxValue(char nomeFile[]) {
  int map[LEN], i, ris, val;
  FILE* in;
  in = fopen(nomeFile, "r");
  memset(map, 0, sizeof(int) * LEN);
  if (in) {
    ris = 0;
    while (fscanf(in, "%d", &val) == 1 && ris != -1)
      if (val >= MIN && val <= MAX)
        map[val]++;
      else
        ris = -1;
    if (ris != -1) {
      for (i = 1; i < LEN; i++) {
        if (map[ris] <= map[i]) {
          ris = i;
        }
      }
    }
  } else {
    printf("Il file non esiste\n");
    ris = -1;
  }
  return ris;
}
