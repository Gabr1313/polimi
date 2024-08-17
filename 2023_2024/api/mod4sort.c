#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
    int v[40];
    srand(time(NULL));
    for (int i = 0; i < 40; i++) v[i] = rand() % 100;
    for (int i = 0; i < 40; i++) printf("%d ", v[i]);
    printf("\n");
    int carry[4] = {0};
    for (int i = 0; i < 40; i++) carry[v[i] % 4]++;
    for (int i = 1; i < 4; i++) carry[i] += carry[i - 1];
    for (int i = 0; i < 40;) {
        if (i < carry[v[i] % 4]) i++;
        else {
            int tmp = v[i];
            v[i] = v[--carry[tmp % 4]];
            v[carry[tmp % 4]] = tmp;
        }
    }
    for (int i = 0; i < 40; i++) printf("%d ", v[i]);
    printf("\n");
    for (int i = 1; i < 40; i++) assert((v[i - 1] % 4) <= (v[i] % 4));
    return 0;
}
