#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* newStr(char car[], int rip[]) {
  char *ris;
  int len, i, j, k;
  len = 1;
  for (i = 0; car[i]; i++) len += rip[i];
  ris = malloc(sizeof(char) * len);
  if (ris) {
    for (i = 0, j = 0; car[i]; i++)
      for (k = 0; k < rip[i]; k++) ris[j++] = car[i];
    ris[j] = '\0';
  }
  return ris;
}

int main(int argc, char* argv[]) {
  char* str;
  int i, len, *arr;
  len = strlen(argv[1]);
  if (argc == len + 2) {
    arr = malloc(len * sizeof(int));
    for (i = 0; i < len; i++) {
      arr[i] = atoi(argv[i + 2]);
    }
    str = newStr(argv[1], arr);
    printf("%s\n", str);
    free(arr);
    free(str);
  }
  return 0;
}
