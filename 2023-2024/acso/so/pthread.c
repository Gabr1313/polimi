#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void* tf(void* tID) {
    int* ptr = malloc(sizeof(int));
    if (ptr == NULL) {
        printf("malloc failed\n");
        exit(1);
    }
    *ptr = 10;
    printf("Thread %d: count = %d\n", *(int*)tID, *ptr);
    return (void*)ptr;
}

int main(void) {
    pthread_t tID1;
    int id1 = 1;
    int *ptr;
    pthread_create(&tID1, NULL, tf, &id1);
    pthread_join(tID1, (void**)&ptr);
    printf("Thread %d: threadExit = %d\n", id1, *ptr);
    free(ptr);
    return 0;
}
