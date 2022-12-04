#include <stdio.h>
#include <stdlib.h>

#define START '('
#define STOP ')'
#define SUBSTITUTE '#'

typedef struct clist_s {
  char val;
  struct clist_s *next;
} clist_t;

clist_t *subseq(clist_t *h) {
  clist_t *el, *del;

  el = h;
  sub = 0;
  while ((el = exists(el, START))) {
    while (el->next->val != STOP) {
      del = pop(el->next);
      free(del);
    }
    el->next = push(el->next, SUBSTITUTE);
    el = el->next;
  }
  return h;
}
