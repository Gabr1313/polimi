#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "ilist.h"

ilist_t *lcompact(ilist_t *);

int main(int argc, char *argv[]) {
  ilist_t *h = NULL;
  int i;
  if (argc > 1) {
    for (i = 1; i < argc; i++) h = lappend(h, atoi(argv[i]));
    lprintf(h);
    h = lcompact(h);
    lprintf(h);
    lfree(h);
  } else
    printf("Usage: %s val1 val2 ...", argv[0]);
  return 0;
}

ilist_t *lcompact(ilist_t *h) {
  ilist_t *el, *tmp;
  h = ldelete(h, 0);
  el = h;
  while (el) {
    tmp = ldelete(el -> next, el->val);
    el -> next = tmp;
    el = tmp;
  }
  return h;
}
