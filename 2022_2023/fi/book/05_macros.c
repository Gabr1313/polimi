#include <stdio.h>
#define LEN 64

/* macros */
#define func(x) x *x + 2
#define printExpr(x) (printf("f(%d) = %d\n", (x), func(x)))
#define printExpr2(x) (printf("inoltre...\n%s = %d\n", #x, (x)))

int main(int argc, char *argv[]) {
    int val;

    scanf("%d", &val);
    printExpr(val);
    printExpr2(2 + 2);

    return 0;
}
