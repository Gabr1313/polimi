#include <stdio.h>
#include <string.h>

#define LEN 20
#define MIN 8
#define MAX 15
#define SPEC "$#%&"

int valido(char username[], int min, int max, char speciali[]) {
  int i;
  char* s;

  for (i = 0, s = NULL; username[i]; i++)
    if (!s) s = strchr(speciali, username[i]);

  return s && i >= min && i <= max;
}

int startApp(char username[]) { return !!username; }

int main(int argc, char* argv[]) {
  char username[LEN + 1];

  do scanf("%s", username);
  while (!valido(username, MIN, MAX, SPEC));

  startApp(username);

  return 0;
}
