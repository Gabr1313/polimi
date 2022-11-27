#include <stdio.h>
#define CASE_1 '1'
#define CASE_2 '2'
#define CASE_3 '3'
#define CASE_4 '4'
#define CASE_5 '5'
#define CASE_6 '6'

int main(int argc, char* argv[]) {
  int a, b, c, delta;
  char sol;
  scanf("%d%d%d", &a, &b, &c);
  if (a == 0) {
    if (b == 0) {
      if (c == 0)
        sol = CASE_1;
      else
        sol = CASE_2;
    } else
      sol = CASE_3;
  } else {
    delta = b * b - 4 * a * c;
    if (delta > 0)
      sol = CASE_4;
    else if (delta < 0)
      sol = CASE_6;
    else
      sol = CASE_5;
  }
  printf("%c\n", sol);
  return 0;
}
