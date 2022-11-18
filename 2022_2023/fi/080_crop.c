/*
Scrivere un sottoprogramma crop che ricevuta in ingresso una stringa frase ed un
carattere ch restituisce una nuova stringa che contiene i caratteri compresi tra la
prima e la seconda occorrenza del carattere ch, incluso il carattere ch. Nel caso in
cui la stringa frase non contenga due occorrenze del carattere ch, restituisce NULL.
ESEMPIO:
in: “informatica”, ‘i’					out: “informati”
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *crop(char[], char);

int main(int argc, char *argv[]) {
    char *cropped;

    if (argc == 3) {
        if ((cropped = crop(argv[1], argv[2][0]))) {
            printf("%s\n", cropped);
            free(cropped);
        }
    } else
        printf("Usage: %s word char\n", argv[0]);

    return 0;
}

char *crop(char frase[], char ch) {
    char *cropped;
    int i, len, found_1, found_2, start;
    size_t len_byte;

    found_1 = 0;
    found_2 = 0;
    for (i = 0; frase[i] && !found_2; ++i)
        if (frase[i] == ch) {
            if (!found_1) {
                found_1 = 1;
                start = i;
            } else {
                found_2 = 1;
                len = i - start + 2;
            }
        }

    if (found_2) {
        len_byte = sizeof(char) * len;
        if ((cropped = malloc(len_byte))) {
            memcpy(cropped, &frase[start], len_byte);
            cropped[len - 1] = '\0';
        } else
            printf("Memory allocation problem with %d char", len);
    } else
        cropped = NULL;

    return cropped;
}
