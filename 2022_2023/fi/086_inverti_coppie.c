/* inverti a coppie gli elementi di una lista */

#include <stdio.h>
#include <stdlib.h>

#include "ilist.h"

ilist_t *invert_pair(ilist_t *);

int main(int argc, char *argv[]) {
  ilist_t *h = NULL, *r;
  int i;
  if (argc > 1) {
    for (i = 1; i < argc; i++) h = lappend(h, atoi(argv[i]));
    r = invert_pair(h);
    lprintf(h);
    lprintf(r);
    lfree(h);
    lfree(r);
  } else
    printf("Usage: %s val1 val2 ...", argv[0]);
  return 0;
}

ilist_t *invert_pair(ilist_t *h) {
  ilist_t *r = NULL, *el;
  while (h && (el = h->next)) {
    r = lappend(r, el->val);
    r = lappend(r, h->val);
    h = el->next;
  }
  if (h) r = lappend(r, h->val);
  return r;
}
