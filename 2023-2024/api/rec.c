#include <stdio.h>
void rec(int n) {
    if (n == 0) return;
    rec(n - 1);
}

int main() {
    for (int i = 1; i < 31; i++) {
        printf("%d -> %d\n", i, 1 << i);
        fflush(stdout);
        rec(1 << i);
    }
}
