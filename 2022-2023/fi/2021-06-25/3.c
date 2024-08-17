#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.h"

/* typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t; */

ilist_t* delMinFinoA(ilist_t* h, ilist_t* stop) {
  int n;
  ilist_t *prec, *el;

  n = stop->val;
  if (h->val < n) {
    while (h->val != n && h->next != stop->next) {
      el = h;
      h = h->next;
      free(el);
    }
  } else {
    prec = h;
    while (prec->next->val > n) prec = prec->next;
    el = prec->next;
    while (el->val != n || el->next != stop->next) {
      prec->next = el->next;
      free(el);
      el = prec->next;
    }
  }
  return h;
}

ilist_t* listaPicchi(ilist_t* h) {
  ilist_t *prec, *el;

  prec = h;
  if (h) {
    el = h->next;
    while (el) {
      if (prec->val <= el->val) h = delMinFinoA(h, el);
      prec = el;
      el = el->next;
    }
  }

  /* prec = h;
  if (h) {
    el = h->next;
    if (el) {
      while (el -> next) {
        if (prec->val <= el->val) h = delMinFinoA(h, el);
        prec = el;
        el = el->next;
      }
      prec -> next = NULL;
      free(el);
    }
  } */

  return h;
}

int main(void) {
  ilist_t* h;
  int val;
  scanf("%d", &val);
  while (val) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }
  listPrintf(h);
  h = listaPicchi(h);
  listPrintf(h);
  listFree(h);
  return 0;
}
