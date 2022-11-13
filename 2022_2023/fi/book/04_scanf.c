#include <stdio.h>
#define SENTINEL 0 

int main (int argc, char *argv[]){
    int input_status, val, sum;
    
    printf("0 = no\n");
    input_status = scanf("%d", &val);
    if (!input_status) {
        printf("Not an integer\n");
    
    if (input_status && val){
        printf("Now i will sum only positive integers\n");
        sum = 0;
        for (input_status = scanf("%d", &val);
                /* loop infinito senza questo controllo */
                input_status == 1 && val <= SENTINEL;
                input_status = scanf("%d", &val))
            sum += val;
        printf("%d\n", sum);
    }

    return 0;
}
