#include <stdio.h>
#include <stdlib.h>

#include "../my_library/ilist.h"

ilist_t* reverseIndex(ilist_t* h, int k) {
  int i;
  ilist_t* el;

  el = h;
  i = 0;
  while (el && i < k) {
    el = el->next;
    i++;
  }
  if (i == k)
    while (el) {
      el = el->next;
      h = h->next;
    }
  else
    h = NULL;

  return h;
}

int main(void) {
  ilist_t *h, *el;
  int val, k;

  scanf("%d", &k);
  scanf("%d", &val);
  while (val) {
    h = listAppend(h, val);
    scanf("%d", &val);
  }

  listPrintf(h);
  el = reverseIndex(h, k);
  printf("%d\n", el->val);
  listFree(h);

  return 0;
}
