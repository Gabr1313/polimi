#include "wlist.h"

wlist_t *list_append(wlist_t *h, char s[]) {
  wlist_t *el, *tail;
  if ((el = malloc(sizeof(wlist_t)))) {
    strcpy(el->word, s);
    el->next = NULL;
    if (!h) {
      h = el;
    } else {
      tail = list_tail(h);
      tail->next = el;
    }
  } else
    printf("list_append: memory allocation error\n");
  return h;
}

wlist_t *list_push(wlist_t *h, char s[]) {
  wlist_t *el;
  if ((el = malloc(sizeof(wlist_t)))) {
    strcpy(el->word, s);
    el->next = h;
    h = el;
  } else
    printf("list_push: memory allocation error\n");
  return h;
}

void list_free(wlist_t *h) {
  wlist_t *del;
  while (h) {
    del = h;
    h = h->next;
    free(del);
  }
}

void list_printf(wlist_t *h) {
  printf("\n");
  if (h && h->next) {
    printf("Start: %s\n", h->word);
    h = h->next;
    printf("Finish: %s\n", list_tail(h)->word);
    if (h) {
      while (h->next->next) {
        printf("%s -> ", h->word);
        h = h->next;
      }
      printf("%s\n", h->word);
    }
  } else
    printf("List is too short\n");
}

wlist_t *list_tail(wlist_t *h) {
  while (h->next) h = h->next;
  return h;
}

wlist_t *list_copy(wlist_t *h) {
  wlist_t *ris = NULL;
  while (h) {
    ris = list_append(ris, h->word);
    h = h->next;
  }
  return ris;
}

char list_del(wlist_t **h_p, char s[]) {
  wlist_t *del, *h;
  char res;
  h = *h_p;
  res = 0;
  if (h && strcmp(h->word, s)) {
    *h_p = h->next;
    free(h);
    res = 1;
  } else if (h) {
    while ((del = h->next) && !res) {
      if (strcmp(del->word, s)) {
        h->next = del->next;
        free(del);
        res = 1;
      } else
        h = del;
    }
  }
  return res;
}

wlist_t *list_pop_head(wlist_t **h_p) {
  wlist_t *h = NULL;
  if ((h = *h_p)) {
    *h_p = h->next;
  }
  return h;
}

wlist_t *list_pop_tail(wlist_t **h_p) {
  wlist_t *tail, *tail_prev;
  if ((tail = *h_p)) {
    if (!(tail->next)) {
      *h_p = NULL;
    } else {
      while (tail->next) {
        tail_prev = tail;
        tail = tail->next;
      }
      tail_prev->next = NULL;
    }
  }
  return tail;
}
