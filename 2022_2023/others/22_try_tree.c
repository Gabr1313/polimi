#include <stdio.h>
#include <stdlib.h>

#define IT_INIT(elem, value)                       \
  do {                                             \
    if ((elem = malloc(sizeof(*elem)))) {          \
      (elem)->val = (value);                       \
      (elem)->bg = NULL;                           \
      (elem)->sm = NULL;                           \
    } else                                         \
      printf("it_add: memory allocation error\n"); \
  } while (0)

typedef signed int i4;

typedef struct tree_s {
  i4 val;
  struct tree_s *bg; /* bigger */
  struct tree_s *sm; /* smaller */
} tree_t;

void it_add(tree_t **, i4); /* integer tree add */
void it_printf(tree_t *);
void it_printf_r(tree_t *);
void it_free(tree_t *);

int main() {
  tree_t *h = NULL;
  i4 val, check;

  /* EOF to finish input (<ctrl><d> in the terminal on linux), or an invalid value */
  check = scanf("%d", &val);
  while (check) {
    it_add(&h, val);
    check = scanf("%d", &val);
  }

  it_printf(h);

  it_free(h);
  return 0;
}

void it_add(tree_t **h_p, i4 val) {
  tree_t *el, *pass;

  if (!*h_p) {
    IT_INIT(el, val);
    *h_p = el;
  } else {
    pass = *h_p;
    while (1) {
      if (val < pass->val) {
        if (pass->sm)
          pass = pass->sm;
        else {
          IT_INIT(el, val);
          pass->sm = el;
          break;
        }
      } else if (val > pass->val) {
        if (pass->bg)
          pass = pass->bg;
        else {
          IT_INIT(el, val);
          pass->bg = el;
          break;
        }
      } else /* if the value is already in the tree */
        break;
    }
  }
}

void it_printf_r(tree_t *h) {
  /* TODO: non ricorsiva */
  if (h) {
    it_printf_r(h->sm);
    printf("%d ", h->val);
    it_printf_r(h->bg);
  } else
    return;
}

void it_printf(tree_t *h) {
  it_printf_r(h);
  printf("\n");
}

void it_free(tree_t *h) {
  /* TODO: non ricorsiva */
  if (h) {
    it_free(h->sm);
    it_free(h->bg);
    free(h);
  } else
    return;
}
