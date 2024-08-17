#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.c"

int isPrime(int n) {
  int ris, i;
  ris = (n < 4 ? n > 1 : n % 2 && n % 3);
  for (i = 5; ris && i*i < n; i+=6) ris = (n % i && n % (i + 2));
  return ris;
}

ilist_t *noPrimeMin(ilist_t *h) {
  ilist_t *elem, *prev;

  if (h) {
    prev = h;
    elem = h->next;
    while (elem) {
      if (elem->val < prev->val && isPrime(elem->val)) {
        prev->next = elem->next;
        free(elem);
        elem = prev->next;
      } else {
        prev = elem;
        elem = prev->next;
      }
    }
  }
  return h;
}

int main(void) {
  ilist_t *h;
  int val;
  scanf("%d", &val);
  while (val) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }
  listPrintf(h);
  noPrimeMin(h);
  listPrintf(h);
  listFree(h);
  return 0;
}
