#include <stdio.h>
#define BASE 10
#define PUD '0'

int main (int argc, char *argv[]){
    int num, tmp, k, ncifre, padding, i;

    do scanf("%d", &num);
    while (num < 0);
    do scanf("%d", &k);
    while (num < 0);

    ncifre = 0;
    tmp = num;
    while (tmp > 0){
        tmp /= BASE;
        ncifre++;
    }

    padding = k - ncifre;

    for (i = 0; i < padding; i++)
        printf("%c",PUD);
    printf("%d\n", num);

    return 0;
}

