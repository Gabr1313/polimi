#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "ilist.h"

int main(int argc, char *argv[]) {
  ilist_t *h = NULL;
  int i;
  if (argc > 1) {
    for (i = 1; i < argc; i++) h = linsert_in_order(h, atoi(argv[i]));
    lprintf(h);
    lfree(h);
  } else
    printf("Usage: %s val1 val2 ...", argv[0]);
  return 0;
}
