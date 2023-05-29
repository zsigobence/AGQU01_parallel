#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define NUM_THREADS 20

typedef struct race_data {
   int thread_id;
   int num_for_rand;
   int lap_time;
   int adv_cars;
   int advantage;
   int max_diff;
}race_data;

void *race(void *arg) {
    race_data* data;
    data = (race_data*)arg;
    
    int adv = 0;
    int thread_id = data->thread_id;
    int race_time;
    int advantage = data->advantage;
    int adv_cars = data->adv_cars;
    int max_diff = data->max_diff;
    int lap_time = data->lap_time;
    srand(time(NULL) + data->num_for_rand);
    printf("%d\n",adv_cars);
    
            if(thread_id < adv_cars){
            adv = advantage * -1;
            }
            if(thread_id >= NUM_THREADS-adv_cars){
            adv = advantage;
            }
            race_time = rand() % max_diff + lap_time + adv; 
            printf("Car %d finished in %d:%d:%d\n", thread_id+1, race_time/60000,(race_time/1000)%60,race_time%1000 );
    
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
    
    for(int race_number = 1;race_number < 4;race_number++){
        for (i = 0; i < NUM_THREADS; i++) {
        race_data[i].thread_id = i;
        race_data[i].num_for_rand = rand()%10000 + 1;
        race_data[i].max_diff = 1200 - race_number * 100;
        race_data[i].lap_time = 80000 + race_number * 15000;
        if(race_number < 3){
            race_data[i].adv_cars = 6 + race_number;
            race_data[i].advantage = 800 + race_number * 100;
        } 
        else{
            race_data[i].adv_cars = 0;
            race_data[i].advantage = 0;
        } 
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
