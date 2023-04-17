#include <omp.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    int array[10];
    long int result=1;
    double time_taken;

    srand(time(0));

    for(int i=0;i<sizeof(array)/sizeof(int);i++){
        array[i] = rand()%10 + 1;
    }

    clock_t t;

    t = clock();
    //szekvenciálisan
    for(int i=0;i<sizeof(array)/sizeof(int);i++){
        result *= array[i];
    }
    t = clock() - t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%d ,%f masodperc alatt",result,time_taken);


    return 0;
}