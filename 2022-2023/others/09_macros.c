#include <stdio.h>
#define LEN 64

/* macros */
#define func(x) (x * x + 2)
#define printExpr(x)                      \
  do {                                    \
    printf("f(%d) = %d\n", (x), func(x)); \
  } while (0)
#define printExpr2(x)                         \
  do {                                        \
    printf("inoltre...\n%s = %d\n", #x, (x)); \
  } while (0)

int main(int argc, char *argv[]) {
  int val;

  scanf("%d", &val);
  printExpr(val);
  printExpr2(2 + 2);

  return 0;
}
