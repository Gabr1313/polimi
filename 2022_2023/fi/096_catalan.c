/* quesito 5 2017-07-03 */

#include <stdio.h>

int cat(int);

int main (void){
  int val, i;

  do scanf("%d", &val);
  while (val <= 0);

  for (i = 0; i <= val; i++)
    printf("%d\n", cat(i));
  return 0;
}

int cat(int n){
  int c, i;
  c = 0;
  if (!n)
    c = 1;
  else 
    for (i = 0; i < n; i++)
      c += cat(i) * cat (n - i - 1);
  return c;
}
