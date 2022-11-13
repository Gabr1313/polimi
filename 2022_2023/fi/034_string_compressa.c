#include <stdio.h>
#define M_RIP 9
#define LEN 100

int main(int argc, char *argv[]) {
    char frase[LEN + 1], fraseCompr[LEN * 2 + 1], letter;
    int i, count, j;

    gets(frase);
    for (i = 0, j = 0; frase[i] != '\0'; j += 2) {
        letter = frase[i];
        count = 1;
        while (frase[i + count] == letter && count < M_RIP)
            count++;
        fraseCompr[j] = '0' + count;
        fraseCompr[j + 1] = letter;
        i += count;
    }
    fraseCompr[j] = '\0';

    puts(fraseCompr);
    return 0;
}
