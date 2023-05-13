#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

double f(double x){
    return sqrt(pow(x,4)-11)/(0.2 * pow(4,(x/2)));
}

int binomial_omp(int n, int k, float p) {
    int i;
    float q = 1 - p;
    float prod = 1;
    #pragma omp parallel for
    for (i = 1; i <= k; i++) {
        prod *= ((float) (n - i + 1) / i) * p / q;
    }
    return (int) (prod * pow(q, n - k) + 0.5);
}

int binomial(int n, int k, float p) {
    int i;
    float q = 1 - p;
    float prod = 1;

    for (i = 1; i <= k; i++) {
        prod *= ((float) (n - i + 1) / i) * p / q;
    }
    return (int) (prod * pow(q, n - k) + 0.5);
}

double poisson(int k, double lambda) {
    double p = exp(-lambda) * pow(lambda, k) / tgamma(k + 1);
    return p;
}

double uniform(double a, double b) {
    double rand_num = rand() / (double)RAND_MAX;  
    double diff = b - a;
    double result = rand_num * diff + a;  
    return result;
}

double exp(double lambda) {
    double u = (double) rand() / RAND_MAX;
    return -log(1 - u) / lambda;
}

//várható érték kiszámítása az integrálást trapéz formulával közelítjük
double expected_v(){
    double a = -1000000;
    double b = 1000000;
    int n = 1000;
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += x*f(x);
    }
    return h * sum;
}

double expected_v_omp(){
    double a = -1000000;
    double b = 1000000;
    int n = 1000;
    double h = (b - a) / n;
    double sum = 0.5 * (f(a) + f(b));
    #pragma omp parallel for
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        sum += x*f(x);
    }
    return h * sum;
}



int main() {
    int t;
    double time_taken;
    FILE* fp;
    fp = fopen("results.txt","a");

    t = clock();
    for(int i = 0; i < 5; i++){
        switch(i){
            case 0:
            binomial(100000,50000,0.4);
            break;
            case 1:
            poisson(5000,3.4);
            break;
            case 2:
            uniform(0,10000);
            break;
            case 3:
            exp(4.2);
            break;
            case 4:
            expected_v();
            break;
        }
    }
    t = clock()- t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Szekvencialisan szukseges ido: %lf\n",time_taken);
    fprintf(fp,"Szekvencialis: %f\n",time_taken);

    t = clock();
    #pragma omp parallel for
    for(int i = 0; i < 5; i++){
        switch(i){
            case 0:
            binomial_omp(10000,5000,0.4);
            break;
            case 1:
            poisson(50,3.4);
            break;
            case 2:
            uniform(0,1000);
            break;
            case 3:
            exp(4.2);
            break;
            case 4:
            expected_v_omp();
            break;
        }
    }
    t = clock()- t;
    time_taken = ((double)t)/CLOCKS_PER_SEC;
    printf("Parhuzamosan szukseges ido: %lf",time_taken);
    
    fprintf(fp,"Parhuzamos: %f\n",time_taken);
    fclose(fp);
    return 0;
}
