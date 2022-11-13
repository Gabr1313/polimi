#include <stdio.h>
#define BASE 10

int isPrime(int);

int main(int argc, char *argv[]) {
    int num, tmp, isTPD;

    do scanf("%d", &num);
    while (num <= 0);

    tmp = num;
    isTPD = 1;
    while (tmp > 0 && isTPD) {
        isTPD = isPrime(tmp);
        tmp /= BASE;
    }

    printf("%d\n", isTPD);
    return 0;
}

int isPrime(int num) {
    int div, isP, meta;
    if (num == 1 || num == 2)
        isP = 1;
    else if (num % 2 == 0)
        isP = 0;
    else {
        meta = num / 2;
        isP = 1;
        for (div = 3; div < meta && isP; div += 2)
            if (num % div == 0)
                isP = 0;
    }

    return isP;
}
