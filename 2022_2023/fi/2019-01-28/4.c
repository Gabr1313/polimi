#include <stdio.h>

#define REP 'x'
#define ZERO '0'
#define ONE '1'

void genera (char * start, char * actual){
  if (*actual){
    if (*actual == REP){
      *actual = ZERO;
      genera (start, actual + 1);
      *actual = ONE;
      genera (start, actual + 1);
      *actual = REP;
    } else
    genera (start, actual + 1);
  } else
  printf("%s\n", start);
} 

int main (int argc, char * argv[]){
  if (argc == 2)
    genera (argv[1], argv[1]);
  else 
    printf("Usage: %s string\n", argv[0]);
  return 0;
}
