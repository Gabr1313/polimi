#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct thread_data {
    int id_fake;
    int* sum;
    pthread_mutex_t* mutex;
} thread_data_t;

void* tf(void* _data) {
    thread_data_t* data = (thread_data_t*)_data;
    printf("Thread %d: waiting\n", data->id_fake);
    pthread_mutex_lock(data->mutex);
    printf("Thread %d: mutex locked\n", data->id_fake);
    *(data->sum) += 1;
    printf("Thread %d: sum = %d\n", data->id_fake, *(data->sum));
    sleep(1);
    *(data->sum) += 1;
    printf("Thread %d: sum = %d\n", data->id_fake, *(data->sum));
    printf("Thread %d: mutex unlocked\n", data->id_fake);
    pthread_mutex_unlock(data->mutex);
    return NULL;
}

int main(void) {
    pthread_t tID1, tID2;
    pthread_mutex_t mutex;
    int sum = 0;
    thread_data_t data1 = {1, &sum, &mutex}, data2 = {2, &sum, &mutex};
    pthread_create(&tID1, NULL, tf, &data1);
    pthread_create(&tID2, NULL, tf, &data2);
    pthread_join(tID1, NULL);
    pthread_join(tID2, NULL);
    printf("sum = %d\n", sum);
    return 0;
}
