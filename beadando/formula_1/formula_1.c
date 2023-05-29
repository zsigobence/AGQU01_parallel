#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 20

typedef struct race_data {
   int thread_id;
   int num_for_rand;
   int race_number;
}race_data;

void *race(void *arg) {
    race_data* data;
    data = (race_data*)arg;
    
    int j = 0;
    int thread_id = data->thread_id;
    int race_number = data->race_number;
    int race_time;
    int advantage = 900;
    int adv_cars = 6;
    int max_diff = 1100;
    int race1_time = 80000;
    int race2_time = 94000;
    int race3_time = 105000;
    srand(time(NULL) + data->num_for_rand);
    switch(race_number){
        case 1:
            if(thread_id < adv_cars){
            j = advantage * -1;
            }
            if(thread_id >= NUM_THREADS-adv_cars){
            j = advantage;
            }
            race_time = rand() % max_diff + race1_time + j; 
            printf("Car %d finished in %d:%d:%d\n", thread_id+1, race_time/60000,(race_time/1000)%60,race_time%1000 );
        break;
        case 2:
            if(thread_id < adv_cars){
            j = advantage * -1;
            }
            if(thread_id >= NUM_THREADS-adv_cars){
            j = advantage;
            }
            race_time = rand() % max_diff + race2_time + j; 
            printf("Car %d finished in %d:%d:%d\n", thread_id+1, race_time/60000,(race_time/1000)%60,race_time%1000 );
        break;
        case 3:
            race_time = rand() % max_diff + race3_time; 
            printf("Car %d finished in %d:%d:%d\n", thread_id+1, race_time/60000,(race_time/1000)%60,race_time%1000 );
        break;
    }
    
    pthread_exit((void*)race_time); 
}


int race_points(int race_results[],int i){
    int placement = 1;
    for(int j = 0;j<NUM_THREADS;j++){
        if(race_results[j] < race_results[i]){
            placement++;
        }
    }
    switch(placement) {
    case 1:
        return 25;
    case 2:
        return 18;
    case 3:
        return 15;
    case 10:
        return 1;
    default:
        if (placement >= 4 && placement < 10) {
            return 12 - (placement - 4) * 2;
        }
        return 0;
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
    void *race_time;
    int i;

    srand(time(NULL));

    for (i = 0; i < NUM_THREADS; i++) {
        car_points[i] = 0;
    }

    for(int race_number = 1;race_number<4;race_number++){
        for (i = 0; i < NUM_THREADS; i++) {
        race_data[i].thread_id = i;
        race_data[i].num_for_rand = rand()%10000 + 1;
        race_data[i].race_number = race_number;
        pthread_create(&threads[i], NULL, race, &race_data[i]);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], &race_time);
        race_results[i] = (int)race_time;
    }
    

    for (i = 0; i < NUM_THREADS; i++) {
        car_points[i] += race_points(race_results,i);
    }

    for (i = 0; i < NUM_THREADS; i++) {
        printf("%d: %d\n",i+1,car_points[i]);
    }
    }
    

    
    printf("And the championship winner is car %d",winner(car_points)+1);
    return 0;
}
