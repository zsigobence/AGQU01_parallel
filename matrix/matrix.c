#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define N 100

void matrixMultiplyOmp(int A[N][N], int B[N][N], int C[N][N]) {
    int i, j, k;

    #pragma omp parallel for private(i, j, k) shared(A, B, C)
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixMultiply(int A[N][N], int B[N][N], int C[N][N]) {
    int i, j, k;

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            C[i][j] = 0;
            for (k = 0; k < N; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void matrixValues(int M[N][N]){
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            M[i][j] = rand() % 3000 + 1;
        }
    }
}


int main() {
    double start_time, end_time;
    double seq_time, par_time;

    int A[N][N];
    int B[N][N];
    int C[N][N];

    matrixValues(A);
    matrixValues(B);
    

    start_time = omp_get_wtime();
    for(int i = 0; i < 2000;i++){
    matrixMultiply(A, B, C);
    }
    end_time = omp_get_wtime();
    seq_time = end_time - start_time;
    printf("Szekvencialisan szukseges ido: %lf\n",seq_time);


    start_time = omp_get_wtime();
    #pragma omp parallel for 
    for(int i = 0; i < 2000;i++){
    matrixMultiplyOmp(A, B, C);
    }
    end_time = omp_get_wtime();
    par_time = end_time - start_time;
    printf("Parhuzamosan szukseges ido: %lf",par_time);
    return 0;
}
