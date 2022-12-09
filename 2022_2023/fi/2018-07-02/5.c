#include <stdio.h>

typedef struct ilist_s {
  int val;
  struct ilist_s *next;
} ilist_t;

ilist_t *select_items(ilist_t * or, int min, int max) {
  ilist_t *h = NULL;

  while (or) {
    if (or->val < max && or->val > min) {
      h = insertup(h, or->val);
    }
    or = or->next;
  }

  return h;
}
