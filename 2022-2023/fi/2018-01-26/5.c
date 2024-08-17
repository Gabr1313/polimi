#include <stdio.h>
#include <stdlib.h>

typedef struct ilist_s {
  int val;
  struct ilist_s *next;
} ilist_t;

ilist_t *delete (ilist_t *h, int val) {
  ilist_t *el, *del;

  while (h && h->val == val) {
    del = h;
    h = h->next;
    free(h);
  }

  el = h;
  while (el && el->next) {
    if (el->next->val == val) {
      del = el->next;
      el->next = del->next;
      free(del);
    } else
      el = el->next;
  }

  return h;
}

ilist_t *del_val_lim(ilist_t *h, int val, int limit) {
  ilist_t *el;
  int count;

  count = 0;
  for (el = h; el && count < limit; el = el->next)
    if (el->val == val) count++;

  if (count == limit) h = delete (h, val);

  return h;
}
