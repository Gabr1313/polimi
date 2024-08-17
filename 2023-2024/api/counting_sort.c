#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct _block {
    int pos, color;
} block;

void print(block* vec, int size) {
    for (int i = 0; i < size; i++) {
        char c = (vec[i].color == 0 ? 'R' : (vec[i].color == 1 ? 'G' : 'B'));
        printf("%c(%d) ", c, vec[i].pos);
    }
    printf("\n");
}

void swap(block* a, block* b) {
    block tmp = *a;
    *a = *b;
    *b = tmp;
}

void sort(block* vec, int size) {
    int red = 0, green = 0, blue = 0;
    for (int i = 0; i < size; i++) {
        if (vec[i].color == 0) red++;
        else if (vec[i].color == 1) green++;
        else if (vec[i].color == 2) blue++;
    }
    blue += (green += --red);
    // printf("%d %d %d\n", red, green, blue);
    for (int i = 0; i < size;) {
        if (vec[i].color == 0 && i < red) swap(&vec[i], &vec[red--]);
        else if (vec[i].color == 1 && i < green) swap(&vec[i], &vec[green--]);
        else if (vec[i].color == 2 && i < blue) swap(&vec[i], &vec[blue--]);
        else i++;

        /* if (vec[i].color == 0 && i < red) {
            swap(&vec[i], &vec[red--]);
            printf("[%d - %d] ", i, red + 1);
        } else if (vec[i].color == 1 && i < green) {
            swap(&vec[i], &vec[green--]);
            printf("[%d - %d] ", i, green + 1);
        } else if (vec[i].color == 2 && i < blue) {
            swap(&vec[i], &vec[blue--]);
            printf("[%d - %d] ", i, blue + 1);
        } else {
            i++;
            continue;
        }
        print(vec, size); */
    }
}

int main(void) {
    int size = 10;
    block* vec = malloc(sizeof(*vec) * size);
    assert(vec);
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        vec[i].pos = i;
        vec[i].color = rand() % 3;
    }
    print(vec, size);
    sort(vec, size);
    print(vec, size);
    free(vec);
    return 0;
}
