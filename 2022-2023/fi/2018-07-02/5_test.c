#include <stdio.h>
#include <stdlib.h>

typedef struct ilist_s {
  int val;
  struct ilist_s* next;
} ilist_t;

ilist_t* linsert_in_order(ilist_t* h, int num) {
  ilist_t *el, *n;
  if ((n = malloc(sizeof(ilist_t)))) {
    n->val = num;
    if (!h || (num <= h->val)) {
      n->next = h;
      h = n;
    } else {
      el = h;
      while (el->next && num > el->next->val) el = el->next;
      n->next = el->next;
      el->next = n;
    }
  } else
    printf("linsert_in_order: allocation problem\n");
  return h;
}

void lprintf(ilist_t* h) {
  for (; h; h = h->next) {
    printf("%d -> ", h->val);
  }
  printf("|\n");
}

ilist_t* lfree(ilist_t* h) {
  ilist_t* del;
  while ((del = h)) {
    h = h->next;
    free(del);
  }
  return h;
}

ilist_t* lappend(ilist_t* h, int num) {
  ilist_t *el, *n;
  if ((n = malloc(sizeof(ilist_t)))) {
    n->val = num;
    n->next = NULL;
    if (h) {
      el = h;
      while (el->next) el = el->next;
      el->next = n;
    } else
      h = n;
  } else
    printf("lappend: allocation problem\n");
  return h;
}

ilist_t* select_items(ilist_t* or, int min, int max) {
  ilist_t* h = NULL;

  while (or) {
    if (or->val < max && or->val > min) {
      h = linsert_in_order(h, or->val);
    }
    or = or->next;
  }

  return h;
}

int main() {
  ilist_t* or, *h;
  int check, min, max, val;

  scanf("%d %d", &min, &max);
  while ((check = scanf("%d", &val))) {
    or = lappend(or, val);
  }

  h = select_items(or, min, max);

  lprintf(or);
  lprintf(h);

  lfree(h);
  lfree(or);
  return 0;
}
