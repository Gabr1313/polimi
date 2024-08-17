#include <stdio.h>

int main (){
  char v[][10]={"I", "am", "Gabriele"};
  /* non posso omettere le dimensioni dopo la prima... a meno di una malloc */

  printf("%s %s %s\n", v[0], v[1], v[2]);

  return 0;
}
