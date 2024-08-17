#include <stdio.h>
#include <ctype.h>

void minMaxStr(char [], char *, char *);

int main (int argc, char * argv[]) {
  char min, max;

  if (argc == 2) {
    minMaxStr(argv[1], &min, &max);
    printf("%c %c\n", min, max);
  } else
    printf("Usage: %s string\n", argv[0]);
  
  return 0;
}

void minMaxStr(char str[], char *min_p, char *max_p) {
  int i;
  char c;

  *min_p = tolower(str[0]);
  *max_p = tolower(str[0]);
  for (i = 0; str[i] != '\0'; i++) {
    c = tolower(str[i]);
    if (c < *min_p)
      *min_p = c;
    else if (c > *max_p)
      *max_p = c; 
  }
}
