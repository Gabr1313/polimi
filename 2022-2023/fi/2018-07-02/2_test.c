#include "2.c"

int main(int argc, char* argv[]) {
  char* s;
  if (argc == 2) {
    s = argv[1];
    shift(s);
    printf("%s\n", s);
  } else
    printf("Usage: %s string\n", argv[0]);

  return 0;
}
