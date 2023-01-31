#include <stdio.h>

#include "../my_library/ilist.h"

/* typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t; */

ilist_t* delFromList(ilist_t* h, int x) {
  ilist_t *el, *del;
  int cnt, n;

  el = h;
  while (el) {
    n = el->val;
    del = el;
    cnt = 1;
    while (cnt < x && (del = listFind(del->next, n))) cnt++;
    if (cnt == x) {
      h = listRemoveInt(h, n);
      el = h;
    } else
      el = el->next;
  }

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

  scanf("%d", &val);
  listPrintf(h);
  h = delFromList(h, val);
  listPrintf(h);
  listFree(h);

  return 0;
}
