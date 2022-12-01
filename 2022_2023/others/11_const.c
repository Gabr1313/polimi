#include <stdio.h>

void reset_arr(const int[], int);

int main(){
  int v[10];
  reset_arr(v, 10);
  return 0;
}

void reset_arr(const int v[], int len){
  int i;
  for (i = 0; i < len; i++)
    v[i] = 0;
  /* il compilatore da' errore perche' e' const  */
}
