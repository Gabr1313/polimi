#include <stdio.h>

#include "../my_library/ilist.h"

ilist_t* manc(ilist_t* h) {
  int i, min, max;
  ilist_t *el, *m = NULL;

  if (h) {
    min = max = h->val;
    el = h->next;
    while (el) {
      if (el->val < min)
        min = el->val;
      else if (el->val > max)
        max = el->val;
      el = el->next;
    }

    for (i = max; i >= min; i--)
      if (!listFind(h, i)) m = listPush(m, i);
  }

  return m;
}

int main(void) {
  ilist_t *h = NULL, *m;
  int el;

  scanf("%d", &el);
  while (el) {
    h = listAppend(h, el);
    scanf("%d", &el);
  }

  m = manc(h);
  listPrintf(h);
  listPrintf(m);

  listFree(h);
  listFree(m);

  return 0;
}
