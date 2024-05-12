
#include <stdio.h>
int main() { // lollll
    long long a = 0, j = 1, k = 0, h;
    for (long long n = 1; n < 100000; n*=2) {
        while (j < n) {
            k++;
            for (int i = 1; i <= k; i++) {
                h = 2;
                while (h < (1 << n)) {
                    a++;
                    h = h * h;
                }
            }
            j *= 2;
        }
        printf("%lld %lld\n", n, a);
    }
}
