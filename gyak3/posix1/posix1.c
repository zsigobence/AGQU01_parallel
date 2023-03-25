#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *compute(void *arg)
{
    int i;
    for (i = 0; i < 4; i++) {
        // Itt jonnek a szamitasok
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t thread;
    int rc;

    // Fo szal
    printf("Fo szal: 8 masodpercnyi szamitas...\n");
    sleep(8);

    // uj szal
    printf("uj szal: 4 masodpercnyi szamitas...\n");
    rc = pthread_create(&thread, NULL, compute, NULL);
    if (rc) {
        fprintf(stderr, "Hiba: A szal letrehozasa nem sikerult, hibakod: %d\n", rc);
        exit(EXIT_FAILURE);
    }

    // Fo szal varja az uj szal befejezeset
    rc = pthread_join(thread, NULL);
    if (rc) {
        fprintf(stderr, "Hiba: A szal befejezese nem sikerult, hibakod: %d\n", rc);
        exit(EXIT_FAILURE);
    }

    printf("A szamitasok befejezodtek!\n");

    return 0;
}
