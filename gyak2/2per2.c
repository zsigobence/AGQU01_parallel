#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void tombgeneral(int elemszam);

int main(){
    clock_t t;
    for(int i = 100;i<3001;i+=200){
    t = clock();
    tombgeneral(i);
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("%d elemszammal %f masodperc alatt futott le \n",i, time_taken);
    }
    return 0;
}

void tombgeneral(int elemszam){
 int tomb[elemszam];
 srand(time(0));
 int flag;
int i = 0;
 while( i<elemszam){
    flag=1;
    tomb[i]=rand()%3000+1;
    for(int j = 0;j<i;j++){
        if(tomb[j]==tomb[i]){
            flag=0;
        }
    }
    if(flag) i++;
 }
 
}