#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
  return (*(char *)a < *(char *)b) - (*(char *)a > *(char *)b);
}

void orderString(char seq[], int n, int m) {
  int tot;
  tot = m - n + 1;
  if (m < strlen(seq)) {
    qsort(&seq[n], tot, sizeof(char), cmp);
  } else
    printf("String too short\n");
}

int main(int argc, char *argv[]) {
  if (argc == 4) {
    orderString(argv[1], atoi(argv[2]), atoi(argv[3]));
    printf("%s\n", argv[1]);
  }
  return 0;
}
