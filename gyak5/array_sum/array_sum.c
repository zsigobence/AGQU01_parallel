#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 100

int array[1000000]; 
int sum = 0; 

void *sum_thread(void *arg) {
    int thread_id = *(int*) arg;
    int start = thread_id * (sizeof(array) / sizeof(int)) / NUM_THREADS;
    int end = (thread_id + 1) * (sizeof(array) / sizeof(int)) / NUM_THREADS;
    int thread_sum = 0;
    for (int i = start; i < end; i++) {
        thread_sum += array[i];
    }
    sum += thread_sum;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];
    srand(time(NULL));
   
    for (int i = 0; i < sizeof(array) / sizeof(int); i++) {
        array[i] = rand() % 100;
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, sum_thread, (void*) &thread_ids[i]);
    }
    
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    printf("Az osszeg: %d\n", sum);
    return 0;
}
