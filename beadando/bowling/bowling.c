#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <omp.h>

#include <Windows.h>

#define ROUNDS 10

int roll_ball(int pins) {
    return rand() % (pins+1);
}

bool is_alldown(int pins) {
    if(pins == 0)
    return true;
    else
    return false;
}


int simulate_bowling_game() {
    int total_score = 0;
    int plus_point = 0;
    
    srand(time(NULL));
    
    for (int round = 1; round <= ROUNDS; round++) {
        //printf("kor: %d\n", round);
        
        int pins = 10;  
    
        int first_roll = roll_ball(pins);
        pins -= first_roll;
        //printf("Dobas 1: %d\n", first_roll);
        
        if (is_alldown(pins)) {
            //printf("Strike!\n\n");
            total_score += 10;
            if(plus_point != 0){
                total_score += 10;
                plus_point++;
            }
            else{
                plus_point += 2;
            }
            continue;
        }
        
        
        int second_roll = roll_ball(pins);
        pins -= second_roll;
        //printf("Dobas 2: %d\n", second_roll);

        

        if(plus_point != 0){
            total_score += first_roll * 2;
            plus_point--;
        }
        else{
            total_score += first_roll;
        }

        if(plus_point != 0){
            total_score += second_roll * 2;
            plus_point--;
        }
        else{
            total_score += second_roll;
        }
        

        if(is_alldown(pins)){
            //printf("Spare!\n");
            plus_point++;
        }
        //printf("Osszpontszam: %d\n\n", total_score);
    }
    
    //printf("Vegeredmeny: %d\n", total_score);
    
    return total_score;
}





int main() {
    double start_time, end_time;
    double seq_time, par_time;
    int n = 100000;
    int max[n];
    int maxindex;
    FILE* fp;
    fp = fopen("results.txt","w");

    start_time = omp_get_wtime();
    for(int i = 0;i<n;i++){
        max[i] = simulate_bowling_game();
    }
    for (int i = 0; i < n - 1; i++) {
        maxindex = i;

        for (int j = i + 1; j < n; j++) {
            if (max[j] > max[maxindex]) {
                maxindex = j;
            }
        }

        int temp = max[i];
        max[i] = max[maxindex];
        max[maxindex] = temp;
    }
    end_time = omp_get_wtime();
    seq_time = end_time - start_time;
    fprintf(fp,"%f\n",seq_time);

    for(int thread_num = 2;thread_num < 21;thread_num++){
    start_time = omp_get_wtime();
    #pragma omp parallel for num_threads(thread_num)
    for(int i = 0;i<n;i++){
        max[i] = simulate_bowling_game();
    }
    #pragma omp parallel for num_threads(thread_num)
    for (int i = 0; i < n - 1; i++) {
        maxindex = i;
        
        for (int j = i + 1; j < n; j++) {
            if (max[j] > max[maxindex]) {
                maxindex = j;
            }
        }

        int temp = max[i];
        max[i] = max[maxindex];
        max[maxindex] = temp;
    }
    end_time = omp_get_wtime();
    par_time = end_time - start_time;
    fprintf(fp,"%d %f\n",thread_num,par_time);
    }
    return 0;
}
