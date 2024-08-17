#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.h"

int isPrimeAbs (int n) {
  int p, i;
  n = abs(n);
  p = (n < 4 ? n > 1 : n % 2 && n % 3);
  for (i = 5; p && i * i < n; i+=6)
    p = (n % i && n % (i + 2));
  return !!p;
}

ilist_t * remAbsPrimes (ilist_t * h) {
  ilist_t * el, * prec;

  while (h && isPrimeAbs(h -> val)) {
    el = h;
    h = h -> next;
    free(el);
  }

  prec = h;
  while ((el = prec -> next)) {
    if (isPrimeAbs(el->val)) {
      prec -> next = el -> next;
      free(el);
    } else 
      prec = el;
  }
  
  return h;
}

int main(void) {
  ilist_t *h = NULL;
  int val, n, i;

  scanf("%d", &n);
  for (i = 0; i < n; i++) {
    scanf("%d", &val);
    h = listAppend(h, val);
  }

  listPrintf(h);
  h = remAbsPrimes(h);
  listPrintf(h);
  listFree(h);

  return 0;
}
