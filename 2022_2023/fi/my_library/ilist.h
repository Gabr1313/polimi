#include <stdio.h>
#include <stdlib.h>

typedef struct ilist_s {
  int val;
  struct ilist_s* next;
} ilist_t;
/*
ilist_t* lappend(ilist_t*, int);
ilist_t* lpush(ilist_t*, int);
ilist_t* linsert_in_order(ilist_t*, int);
ilist_t* lfind(ilist_t*, int);
ilist_t* ldelete(ilist_t*, int);
void free_list(ilist_t*);
int llen(ilist_t*);
void lprintf(ilist*);
ilist_t* lpop(ilist_t*, int);
*/
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

ilist_t* lpush(ilist_t* h, int num) {
  ilist_t* n;
  if ((n = malloc(sizeof(ilist_t)))) {
    n->val = num;
    n->next = h;
    h = n;
  } else
    printf("lpush: allocation problem\n");
  return h;
}

ilist_t* linsert_in_order(ilist_t* h, int num) {
  ilist_t *el, *n;
  if ((n = malloc(sizeof(ilist_t)))) {
    n->val = num;
    el = h;
    while ((el = el->next) && el->val < num)
      ;
    n->next = el;
    el = n;
  } else
    printf("linsert_in_order: allocation problem\n");
  return h;
}

ilist_t* lfind(ilist_t* h, int num) {
  ilist_t* el;
  el = h;
  if (h)
    while ((el = el->next) && el->val != num)
      ;
  return el;
}

ilist_t* ldelete(ilist_t* h, int num) {
  ilist_t *pre, *del;
  while (h && h->val == num) {
    del = h;
    h = h->next;
    free(del);
  }
  if (h) {
    pre = h;
    while ((del = pre->next)) {
      if (del->val == num) {
        pre->next = del->next;
        free(del);
      } else
        pre = del;
    }
  }
  return h;
}

void lfree(ilist_t* h) {
  ilist_t* del;
  while ((del = h)) {
    h = h->next;
    free(del);
  }
}

int llen(ilist_t* h) {
  int len;
  len = 0;
  if (h)
    while ((h = h->next)) len++;
  return len;
}

void lprintf(ilist_t* h) {
  if (h) {
    while (h->next) {
      printf("%d -> ", h->val);
      h = h->next;
    }
    printf("%d\n", h->val);
  }
}

ilist_t* lpop(ilist_t* h, int pos) {
  ilist_t *el, *del;
  int i;
  if (!pos) {
    el = h;
    h = h->next;
    free(el);
  } else if (pos > 0) {
    el = h;
    for (i = 1; i < pos && el->next; i++) el = el->next;
    if (i == pos) {
      del = el->next;
      el->next = del->next;
      free(del);
    } else
      printf("Pop: index out of range\n");
  } else {
    el = h;
    del = el->next;
    while (del->next) {
      el = del;
      del = el->next;
    }
    el->next = NULL;
    free(del);
  }
  return h;
}
