#include "ilist.h"

ilist_t* listAppend(ilist_t* h, int num) {
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
    printf("listAppend: allocation problem\n");
  return h;
}

ilist_t* listPush(ilist_t* h, int num) {
  ilist_t* n;
  if ((n = malloc(sizeof(ilist_t)))) {
    n->val = num;
    n->next = h;
    h = n;
  } else
    printf("listPush: allocation problem\n");
  return h;
}

ilist_t* listInsertInOrder(ilist_t* h, int num) {
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
    printf("linsertInOrder: allocation problem\n");
  return h;
}

ilist_t* listFind(ilist_t* h, int num) {
  ilist_t* el;
  el = h;
  if (h)
    while ((el = el->next) && el->val != num)
      ;
  return el;
}

ilist_t* listRemoveInt(ilist_t* h, int num) {
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

ilist_t* listRemovePos(ilist_t* h, int pos) {
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
      printf("listRemovePos: index out of range\n");
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

ilist_t* listFree(ilist_t* h) {
  ilist_t* del;
  while ((del = h)) {
    h = h->next;
    free(del);
  }
  return h;
}

int listLen(ilist_t* h) {
  int len;
  len = 0;
  if (h)
    while ((h = h->next)) len++;
  return len;
}

void listPrintf(ilist_t* h) {
  for (; h; h = h->next) {
    printf("%d -> ", h->val);
  }
  printf("|\n");
}

/* void lprintf(ilist_t* h) {
  if (h) {
    while (h->next) {
      printf("%d -> ", h->val);
      h = h->next;
    }
    printf("%d\n", h->val);
  }
} */

ilist_t* listPopHead(ilist_t** h_p) {
  ilist_t* el;
  el = (*h_p);
  *h_p = el->next;
  return el;
}

ilist_t* listPopTail(ilist_t** h_p) {
  ilist_t *el, *prev;

  el = (*h_p);
  if (el && el->next) {
    while (el->next) {
      prev = el;
      el = el->next;
    }
    prev->next = NULL;
  } else if (el) {
    (*h_p) = NULL;
  }

  return el;
}
