#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.h"

ilist_t * ruotaSx(ilist_t *);
ilist_t * ruotaDx(ilist_t *);

ilist_t * ruota (ilist_t * h, int dir) {
  if (h && h -> next) {
    if (dir)
      h = ruotaDx(h);
    else 
      h = ruotaSx(h);
    return h;
  }

  return h;
}

ilist_t * ruotaSx(ilist_t * h) {
  ilist_t * el, * prec;

  el = h;
  h = prec = h -> next;
  while (prec -> next)
    prec = prec -> next;
  prec -> next = el;
  el -> next = NULL;

  return h;
}

ilist_t * ruotaDx(ilist_t * h) {
  ilist_t * el, * prec;

  prec = h;
  while (prec -> next -> next)
    prec = prec -> next;
  el = prec -> next;
  prec -> next = NULL;
  el -> next = h;

  return el;
}


int main (void) {
  ilist_t * h;
  int n;

  scanf("%d", &n);
  while (n) {
    h = listAppend(h, n);
    scanf("%d", &n);
  }

  listPrintf(h);
  h = ruota(h, 0);
  listPrintf(h);
  h = ruota(h, 1);
  h = ruota(h, 1);
  listPrintf(h);
  listFree(h);

  return 0;
}
