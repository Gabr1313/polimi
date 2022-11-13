#include <stdio.h>

int main (int argc, char *argv[]){
    int scelta;
    
    scanf("%d", &scelta);

    switch(scelta){
        case 1: printf("Scelta 1\n");
        case 2: printf("Scelta 1 o 2\n");
                break;
        case 3: printf("Scelta 3\n");
                break;
        default: printf("Non tra le prime 3 scelte\n");
    }

    return 0;
}

