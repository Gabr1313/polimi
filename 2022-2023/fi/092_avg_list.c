#include <stdio.h>
#include <stdlib.h>

#include "ilist.h"

ilist_t *l_avg(ilist_t *);

int main(int argc, char *argv[]) {
  ilist_t *h = NULL, *m;
  int i;
  if (argc > 2) {
    for (i = 1; i < argc; i++) h = lappend(h, atoi(argv[i]));
    m = l_avg(h);
    lprintf(h);
    lprintf(m);
    lfree(h);
    lfree(m);
  } else
    printf("Usage: %s val1 val2 ...", argv[0]);
  return 0;
}

ilist_t *l_avg(ilist_t *h) {
  int val;
  ilist_t *m = NULL;
  while (h && h->next) {
    val = (h->val + h->next->val) / 2;
    m = lappend(m, val);
    h = h->next;
  }
  return m;
}
