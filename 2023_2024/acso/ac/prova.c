#include <stdio.h>
#define N 7
typedef long long int LONG;
LONG code = 18;
char LETTERS[N] = {1, 2, 3, 4, 5, 6, 7}; /* N.B: in C il char è un numero con segno */
/* funzione chksum */
LONG chksum(char *byte, LONG weight) {
  LONG idx;
  LONG *ptr;
  LONG partial;
  ptr = &partial;
  *ptr = 0;
  for (idx = N - 1; idx >= 0; idx--) {
    *ptr = *ptr + byte[idx] - weight;
    weight++;
  } /* for */
  return *ptr;
} /* chksum */
/* programma principale */
int main() {
  code = chksum(LETTERS, code);
  printf("code = %lld\n", code);
  return 0;
}
