#include <stdio.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 60

void *work(void *arg) {
    printf("Thread %ld started.\n", (long) arg);
    sleep(1);
    printf("Thread %ld ended.\n", (long) arg);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for (t = 0; t < NUM_THREADS; t++) {
        rc = pthread_create(&threads[t], NULL, work, (void *) t);
        if (rc) {
            printf("ERROR: Return code from pthread_create() is %d\n", rc);
            return 1;
        }
    }

    for (t = 0; t < NUM_THREADS; t++) {
        pthread_join(threads[t], NULL);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total time taken: %f seconds\n", cpu_time_used);

    pthread_exit(NULL);
}
