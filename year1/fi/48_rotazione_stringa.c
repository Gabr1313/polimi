#include <stdio.h>
#include <string.h>
#define LEN 50

int main (int argc, char *argv[]){
    char frase[LEN + 1], fraseR[LEN + 1];
    int i, len, ruota, j;

    gets(frase);
    scanf("%d", &ruota);

    len = strlen(frase);
    for (i = 0; i < len; i++){
        j = i - ruota;
        if (j < 0)
            j += len;
        fraseR[i] = frase [j];
    }
    fraseR[len] = '\0';

    printf("%s\n", fraseR);
    return 0;
}
    

    
