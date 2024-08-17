#include <semaphore.h>

int main(void) {
    sem_t sem;
    sem_init(&sem, 0, 1);
    return 0;
}
