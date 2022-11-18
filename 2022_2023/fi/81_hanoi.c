#include <stdio.h>
#define START 'A'
#define TEMP 'B'
#define FINISH 'C'

void hanoi(int, char, char, char);

int main (int argc, char *argv[])
{
    int depth;

    do scanf("%d", &depth);
    while (depth <= 0);

    hanoi(depth, START, FINISH, TEMP);

    return 0;
}

void hanoi(int depth, char start, char finish, char temp){
    if (depth == 1)
        printf("Move %d from %c to %c\n", depth, start, finish);
    else {
        hanoi(depth - 1, start, temp, finish);
        printf("Move %d from %c to %c\n", depth, start, finish);
        hanoi(depth - 1, temp, finish, start);
    }
}
