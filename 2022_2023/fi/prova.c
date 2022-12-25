#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
  char s1[]="nonSoCosaScrivere";
  printf("%s\n",s1);

  memmove(s1, s1 + 5, 10);
  printf("%s\n",s1);

  strcpy(s1, "nonSoCosaScrivere");
  memmove(s1 + 5, s1, 10);
  printf("%s\n",s1);
  return 0;
}
