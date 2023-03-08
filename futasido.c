#include <stdio.h>
#include <time.h>

void primszamok(int intervall);

int main(){
FILE* fpointer;
fpointer = fopen("futasido.txt","a");
clock_t t;
for(int i=1000;i<25000;i+=1000){
t = clock();
primszamok(i);
t = clock() - t;
double time_taken = ((double)t)/CLOCKS_PER_SEC;
printf(" %f masodperc alatt futott le \n", time_taken);
fprintf(fpointer,"%d,%lf\n",i,time_taken);
}
    return 0;
}

void primszamok(int intervall){
    int db;
    int primszamdb = 0;
    for(int i=0;i<intervall;i++){
        db = 0;
        for(int j =1;j<i+1;j++){
            if(i%j==0){
                db++;
            }
        }
        if(db==2){
            primszamdb++;
        }
    }
}