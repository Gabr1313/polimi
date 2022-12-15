/* un sottoprogramma che ricevuto in ingresso un array di interi e un valore n, calcola le medie mobili  */

#define LEN 10

#include <stdio.h>
#include <stdlib.h>

float * media_mobile(int * v, int len, int n){
  int i, j, sum, n_tmp;
  float *ris;

  if ((ris = malloc(len * sizeof(float)))){
    sum = 0;
    n_tmp = 0;
    for (i = 0; i < n; i++){
      sum += v[i];
      n_tmp ++;
      ris[i] = (float)sum/n_tmp;
    }
    for (j = 0; i < len; i++, j++){
      sum = sum - v[j] + v[i];
      ris[i] = (float)sum/n;
    }
  }
  else{
    printf("media_mobile: problem with memory allocation\n");
    return NULL;
  }
  return ris;
}

int main (void){
  int v[LEN],val, i, len, n;
  float *ris;

  len = 0;
  scanf("%d", &n);
  while ((scanf("%d", &val)) && len < LEN){
    v[len] = val;
    len++;
  }

  ris = media_mobile(v, len, n);

  for (i = 0; i < len;i++)
    printf("%g ", ris[i]);
  printf("\n");

  free(ris);

  return 0;
}
