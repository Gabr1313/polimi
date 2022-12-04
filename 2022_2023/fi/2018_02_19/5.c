#include <stdio.h>

typedef struct ilist_s {
  int val;
  struct ilist_s* next;
} ilist_t;

int kcon(ilist_t* h, int k) {
  if (!(h && h->next)) return 0;
  if (h && h->next && h->val == k && h->next->val == k) return 1;
  return kcon(h->next, k);
}

int isthere(ilist_t* h, int k) {
  while (h) {
    if (h->val == k) return 1;
    h = h->next;
  }
  return 0;
}

int knocon(ilist_t* h, int k) {
  while (h) {
    if (h->val == k && h->next && isthere(h->next->next, k)) return 1;
    h = h->next;
  }
  return 0;
}
