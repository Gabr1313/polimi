#include <stdio.h>
#include <stdlib.h>

typedef struct clist_s {
  char val;
  struct clist_s* next;
} clist_t;
/*
clist_t* cappend(clist_t*, char);
clist_t* cpush(clist_t*, char);
clist_t* cinsert_in_order(clist_t*, char);
clist_t* cfind(clist_t*, char);
clist_t* cdelete(clist_t*, char);
void cfree(clist_t*);
char clen(clist_t*);
void cprintf(ilist*);
clist_t* cpop(clist_t*, char);
*/
clist_t* cappend(clist_t* h, char num) {
  clist_t *el, *n;
  if ((n = malloc(sizeof(clist_t)))) {
    n->val = num;
    n->next = NULL;
    if (h) {
      el = h;
      while (el->next) el = el->next;
      el->next = n;
    } else
      h = n;
  } else
    printf("cappend: allocation problem\n");
  return h;
}

clist_t* cpush(clist_t* h, char num) {
  clist_t* n;
  if ((n = malloc(sizeof(clist_t)))) {
    n->val = num;
    n->next = h;
    h = n;
  } else
    printf("cpush: allocation problem\n");
  return h;
}

clist_t* cinsert_in_order(clist_t* h, char num) {
  clist_t *el, *n;
  if ((n = malloc(sizeof(clist_t)))) {
    n->val = num;
    if (!h) {
      h = n;
      h->next = NULL;
    } else if (num < h->val) {
      n->next = h;
      h = n;
    } else {
      el = h;
      while (el->next && num > el->next->val)
        el = el -> next;
      n -> next = el -> next;
      el -> next = n;
    }

  } else
    printf("cinsert_in_order: allocation problem\n");
  return h;
}

clist_t* cfind(clist_t* h, char num) {
  clist_t* el;
  el = h;
  if (h)
    while ((el = el->next) && el->val != num)
      ;
  return el;
}

clist_t* cdelete(clist_t* h, char num) {
  clist_t *pre, *del;
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

void cfree(clist_t* h) {
  clist_t* del;
  while ((del = h)) {
    h = h->next;
    free(del);
  }
}

int clen(clist_t* h) {
  int len;
  len = 0;
  if (h)
    while ((h = h->next)) len++;
  return len;
}

void cprintf(clist_t* h) {
  if (h) {
    while (h->next) {
      printf("%c -> ", h->val);
      h = h->next;
    }
    printf("%c\n", h->val);
  }
}

clist_t* cpop(clist_t* h, int pos) {
  clist_t *el, *del;
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
      printf("cpop: index out of range\n");
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
