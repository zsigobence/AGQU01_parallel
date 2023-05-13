#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 20

typedef struct race_data {
   int thread_id;
   int num_for_rand;
}race_data;

void *race1(void *arg) {
    race_data* data;
    data = (race_data*)arg;
    
    int j = 0;
    int thread_id = data->thread_id;
    srand(time(NULL) + data->num_for_rand);
    if(thread_id < 6){
        j = -100;
    }
    if(thread_id > 15){
        j = 100;
    }
    int wait_time = rand() % 1000 + 80000 + j; 

    printf("Car %d finished in %d:%d:%d\n", thread_id+1, wait_time/60000,(wait_time/1000)%60,wait_time%1000 );
    pthread_exit((void*)wait_time); 
}

void *race2(void *arg) {
    race_data* data;
    data = (race_data*)arg;
    
    int j = 0;
    int thread_id = data->thread_id;
    srand(time(NULL) + data->num_for_rand);
    if(thread_id < 8){
        j = -1;
    }
    if(thread_id > 11){
        j = 1;
    }
    int wait_time = rand() % 1100 + 94000 + j; 

    printf("Car %d finished in %d:%d:%d\n", thread_id+1, wait_time/60000,(wait_time/1000)%60,wait_time%1000 );
    pthread_exit((void*)wait_time); 
}

void *race3(void *arg) {
    race_data* data;
    data = (race_data*)arg;
    
    int thread_id = data->thread_id;
    srand(time(NULL) + data->num_for_rand);
    int wait_time = rand() % 1200 + 105000; 

    printf("Car %d finished in %d:%d:%d\n", thread_id+1, wait_time/60000,(wait_time/1000)%60,wait_time%1000 );
    pthread_exit((void*)wait_time); 
}

int race_points(int race_results[],int i){
    int placement = 1;
    for(int j = 0;j<NUM_THREADS;j++){
        if(race_results[j] < race_results[i]){
            placement++;
        }
    }
    switch(placement){
        case 1:
        return 25;
        break;
        case 2:
        return 18;
        break;
        case 3:
        return 15;
        break;
        case 4:
        return 12;
        break;
        case 5:
        return 10;
        break;
        case 6:
        return 8;
        break;
        case 7:
        return 6;
        break;
        case 8:
        return 4;
        break;
        case 9:
        return 2;
        break;
        case 10:
        return 1;
        break;
        default:
        return 0;
        break;
    }
}

int winner(int car_points[]){
    int winner_index = 0;
    for(int i = 1;i < 20;i++){
        if(car_points[i] > car_points[winner_index]){
            winner_index = i;
        }
    }
    return winner_index;
}

int main() {
    pthread_t threads[NUM_THREADS];
    int race_results[NUM_THREADS];
    int car_points[NUM_THREADS];
    race_data race_data[NUM_THREADS];
    void *wait_time;
    int i;

    srand(time(NULL));

    for (i = 0; i < NUM_THREADS; i++) {
        car_points[i] = 0;
    }
    

    for (i = 0; i < NUM_THREADS; i++) {
        race_data[i].thread_id = i;
        race_data[i].num_for_rand = rand()%10000 + 1;
        pthread_create(&threads[i], NULL, race1, &race_data[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &wait_time);
        race_results[i] = (int)wait_time;
    }
    

    for (i = 0; i < NUM_THREADS; i++) {
        car_points[i] += race_points(race_results,i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        printf("%d\n",car_points[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        race_data[i].thread_id = i;
        race_data[i].num_for_rand = rand()%10000 + 1;
        pthread_create(&threads[i], NULL, race2, &race_data[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &wait_time);
        race_results[i] = (int)wait_time;
    }
    

    for (i = 0; i < NUM_THREADS; i++) {
        car_points[i] += race_points(race_results,i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        printf("%d\n",car_points[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        race_data[i].thread_id = i;
        race_data[i].num_for_rand = rand()%10000 + 1;
        pthread_create(&threads[i], NULL, race3, &race_data[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &wait_time);
        race_results[i] = (int)wait_time;
    }
    

    for (i = 0; i < NUM_THREADS; i++) {
        car_points[i] += race_points(race_results,i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        printf("%d\n",car_points[i]);
    }

    printf("And the championship winner is car %d",winner(car_points)+1);
    return 0;
}
