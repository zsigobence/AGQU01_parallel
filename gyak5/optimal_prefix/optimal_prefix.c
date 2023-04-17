#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
    int n, i, j, *a, *b;

    if (argc < 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    n = atoi(argv[1]);

    a = malloc(n * sizeof(int));
    b = malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        a[i] = i + 1;
    }

    b[0] = a[0];

    #pragma omp parallel for
    for (i = 1; i < n; i++) {
        b[i] = b[i - 1] + a[i];
    }

    printf("Prefix sum:\n");

    for (i = 0; i < n; i++) {
        printf("%d ", b[i]);
    }

    printf("\n");

    free(a);
    free(b);

    return 0;
}
