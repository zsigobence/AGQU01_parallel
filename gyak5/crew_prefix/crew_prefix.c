#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void prefix_sum(int* arr, int n) {
    int* sum = (int*)malloc(n * sizeof(int));
    #pragma omp parallel for
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            sum[i] = arr[i];
        } else {
            sum[i] = arr[i] + sum[i - 1];
        }
    }

    for (int i = 0; i < n; i++) {
        arr[i] = sum[i];
    }

    free(sum);
}

int main() {
    int n = 10000000;
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = 1;
    }

    double start_time = omp_get_wtime();
    prefix_sum(arr, n);
    double end_time = omp_get_wtime();

    printf("Execution time: %f seconds\n", end_time - start_time);

    free(arr);
    return 0;
}
