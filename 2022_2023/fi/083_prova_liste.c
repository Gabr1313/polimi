#include <stdio.h>
#include "ilist.h"
#include "vect.h"

int main (){
  ilist_t * h = NULL;
  h = lappend(h, 3);
  h = lappend(h, 6);
  h = lappend(h, 7);
  lprintf(h);
  printf("\n");
  h = lpop(h, 9);
  lprintf(h);
  lfree(h);
  printf("funziona\n");
  return 0;
}
