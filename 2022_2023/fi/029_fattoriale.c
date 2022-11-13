#include <stdio.h>

int main (int argc, char *argv[]){
    int num, fact;

    do scanf ("%d", &num);
    while (num < 0);

    fact = 1;
    while (num > 0){
        fact *= num;
        num--;
    }

    printf ("%d\n", fact);
    return 0;
}
