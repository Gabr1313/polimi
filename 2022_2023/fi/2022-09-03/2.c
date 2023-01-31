#include <stdio.h>
#include <stdlib.h>

float mediaNoDup(int v[], int len) {
  int found, i, j, sum, cnt;

  for (i = sum = cnt = 0; i < len; i++) {
    found = 0;
    for (j = i + 1; j < len && !found; j++) found = v[i] == v[j];
    if (!found) {
      sum += v[i];
      cnt++;
    }
  }

  return (float)sum / cnt;
}

#define LEN 100
int main(void) {
  int v[LEN], len, i;

  scanf("%d", &len);
  for (i = 0; i < len; i++) scanf("%d", &v[i]);

  printf("%g\n", mediaNoDup(v, len));

  return 0;
}
