#include <stdio.h>
#define LOW_MIN 'a'
#define LOW_MAX 'z'
#define UPP_MIN 'A'
#define UPP_MAX 'Z'
#define NUM_MIN '0'
#define NUM_MAX '9'
#define SPACE ' '

int trim(char s[]) {
  int i, delta;
  delta = 0;
  for (i = 0; s[i]; i++) {
    if (!((s[i] >= LOW_MIN && s[i] <= LOW_MAX) ||
          (s[i] >= UPP_MIN && s[i] <= UPP_MAX) ||
          (s[i] >= NUM_MIN && s[i] <= NUM_MAX) || (s[i] == SPACE)))
      delta++;
    else
      s[i - delta] = s[i];
  }
  s[i - delta] = s[i];
  return delta;
}

#define LEN 200

int main(void) {
  char frase[LEN + 1];
  fgets(frase, LEN + 1, stdin);
  trim(frase);
  puts(frase);
  return 0;
}
