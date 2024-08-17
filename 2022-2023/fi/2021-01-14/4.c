#include <stdio.h>

#include "../my_library/ilist.c"

/* typedef struct ilist_s {
  int val;
  struct ilist_s * next;
} ilist_t; */

ilist_t* compatta(ilist_t* h) {
  ilist_t* el;

  h = listRemoveInt(h, 0);
  el = h;
  while (el) {
    el->next = listRemoveInt(el->next, el->val);
    el = el->next;
  }

  return h;
}

/*
h = compatta (h);
*/

#define LEN 10

int main(void) {
  ilist_t* h;
  int val, i;
  for (i = 0; i < LEN; i++) {
    scanf("%d", &val);
    h = listAppend(h, val);
  }
  listPrintf(h);
  h = compatta(h);
  listPrintf(h);
  listFree(h);

  return 0;
}
