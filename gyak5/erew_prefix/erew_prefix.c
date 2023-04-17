#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void erew_prefix_sum(int* arr, int n) {
    int i, j;

    for (i = 1; i < n; i *= 2) {
        #pragma omp parallel for private(j) shared(arr)
        for (j = i; j < n; j++) {
            arr[j] += arr[j - i];
        }
    }
}

int main() {
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int n = sizeof(arr) / sizeof(arr[0]);
    int i;

    printf("Original array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    double start_time = omp_get_wtime();
      erew_prefix_sum(arr, n);
    double end_time = omp_get_wtime();

   
  

    printf("Prefix sum array:\n");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    
    printf("Execution time: %f seconds\n", end_time - start_time);

    return 0;
}
