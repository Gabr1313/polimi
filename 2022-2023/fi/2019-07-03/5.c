#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.c"

/* typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t; */

int isPrimeAbs(int n) {
  int ris, i;
  n = abs(n);
  if (n == 0 || n == 1)
    ris = 0;
  else if (n == 2 || n == 3)
    ris = 1;
  else if (n % 2 == 0 || n % 3 == 0)
    ris = 0;
  else {
    ris = 1;
    for (i = 5; i * i < n && ris; i += 6)
      if (n % i == 0 || n % (i + 2) == 0) ris = 0;
  }
  return ris;
}

/* funzione da imparare, molto piu' corta */
/* int primeAbs(int n) {
  int p, i;
  n = abs(n);
  p = (n < 4 ? n > 1 : (n % 2 && n % 3));
  for (i = 5; p && i * i <= n; i += 6) p = (n % i && n % (i + 2));
  return p;
} */


ilist_t *deletePrimes(ilist_t *h) {
  ilist_t *elem, *prev;
  while (h && isPrimeAbs(h->val)) {
    elem = h;
    h = h->next;
    free(elem);
  }
  prev = h;
  elem = prev->next;
  while (elem) {
    if (isPrimeAbs(elem->val)) {
      prev->next = elem->next;
      free(elem);
      elem = prev->next;
    } else {
      prev = elem;
      elem = elem->next;
    }
  }
  return h;
}

int main(void) {
  int val;
  ilist_t *h = NULL;

  scanf("%d", &val);
  while (val > 0) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }
  listPrintf(h);
  h = deletePrimes(h);
  listPrintf(h);

  listFree(h);
  return 0;
}
