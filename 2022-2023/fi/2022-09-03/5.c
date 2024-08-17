#include <stdio.h>

#include "../my_library/ilist.h"

ilist_t* setunione(ilist_t* h1, ilist_t* h2) {
  ilist_t *r = NULL, *prec, *el;

  if (h1 && h2) {
    if (h1->val < h2->val) {
      el = h1;
      h1 = h1->next;
    } else {
      el = h2;
      h2 = h2->next;
    }
    r = listAppend(r, el->val);
  } else if (h1) {
    r = listAppend(r, h1->val);
    h1 = h1->next;
  } else if (h2) {
    r = listAppend(r, h2->val);
    h2 = h2->next;
  }
  prec = r;

  while (h1 && h2) {
    if (h1->val < h2->val) {
      el = h1;
      h1 = h1->next;
    } else {
      el = h2;
      h2 = h2->next;
    }
    if (el->val != prec->val) {
      prec = listAppend(prec, el->val);
      prec = prec->next;
    }
  }

  while (h1) {
    if (h1->val != prec->val) {
      prec = listAppend(prec, h1->val);
      prec = prec->next;
    }
    h1 = h1->next;
  }

  while (h2) {
    if (h2->val != prec->val) {
      prec = listAppend(prec, h2->val);
      prec = prec->next;
    }
    h2 = h2->next;
  }

  return r;
}

int main(void) {
  int val;
  ilist_t *h1 = NULL, *h2 = NULL, *h3;

  scanf("%d", &val);
  while (val) {
    h1 = listAppend(h1, val);
    scanf("%d", &val);
  }

  scanf("%d", &val);
  while (val) {
    h2 = listAppend(h2, val);
    scanf("%d", &val);
  }

  h3 = setunione(h1, h2);

  listPrintf(h1);
  listPrintf(h2);
  listPrintf(h3);

  listFree(h1);
  listFree(h2);
  listFree(h3);

  return 0;
}
