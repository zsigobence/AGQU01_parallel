#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

#define ARRAY_SIZE 100000
void fill_array(int array[]){
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 100000;
    }
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high-1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[high]);
    return (i+1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
                quick_sort(arr, low, pi - 1);
            

                quick_sort(arr, pi + 1, high);
        
    }
}

void bubble_sort(int arr[]) {
   int i, j;
   for (i = 0; i < ARRAY_SIZE-1; i++) {
       for (j = 0; j < ARRAY_SIZE-i-1; j++) {
           if (arr[j] > arr[j+1]) {
              int temp = arr[j];
              arr[j] = arr[j+1];
              arr[j+1] = temp;
           }
       }
   }
}

void insertion_sort(int arr[]) {
   int i, key, j;
   for (i = 1; i < ARRAY_SIZE; i++) {
       key = arr[i];
       j = i - 1;
       while (j >= 0 && arr[j] > key) {
           arr[j + 1] = arr[j];
           j = j - 1;
       }
       arr[j + 1] = key;
   }
}


void heapify(int arr[], int n, int i) {
   int largest = i;
   int l = 2*i + 1;
   int r = 2*i + 2;
   if (l < n && arr[l] > arr[largest]) {
       largest = l;
   }
   if (r < n && arr[r] > arr[largest]) {
       largest = r;
   }
   if (largest != i) {
       int temp = arr[i];
       arr[i] = arr[largest];
       arr[largest] = temp;
       heapify(arr, n, largest);
   }
}

void heap_sort(int arr[]) {
   for (int i = ARRAY_SIZE / 2 - 1; i >= 0; i--) {
       heapify(arr, ARRAY_SIZE, i);
   }
   for (int i = ARRAY_SIZE - 1; i > 0; i--) {
       int temp = arr[0];
       arr[0] = arr[i];
       arr[i] = temp;
       heapify(arr, i, 0);
   }
}
void minselection_sort(int arr[]) {
   int i, j, min_idx;
   
   for (i = 0; i < ARRAY_SIZE-1; i++) {
       min_idx = i;
       for (j = i+1; j < ARRAY_SIZE; j++) {
           if (arr[j] < arr[min_idx]) {
               min_idx = j;
           }
       }
       
       int temp = arr[i];
       arr[i] = arr[min_idx];
       arr[min_idx] = temp;
   }
}
int main() {
    int arr[ARRAY_SIZE];
    clock_t t_seq,t_all,t_quick,t_bubble,t_insertion,t_heap,t_minselect;
    double time_taken;
    
    t_all = clock();
    #pragma omp parallel for
    for(int i = 0;i<5;i++){
        srand(time(NULL));
        fill_array(arr);
        switch(i){
            case 0:
                t_quick = clock();
                quick_sort(arr, 0, ARRAY_SIZE-1);
                t_quick = clock() - t_quick;
                time_taken = ((double)t_quick)/CLOCKS_PER_SEC;
                printf("Gyors rendezes: %lf\n",time_taken);

                break;
            case 1:
                t_bubble = clock();
                bubble_sort(arr);
                t_bubble = clock() - t_bubble;
                time_taken = ((double)t_bubble)/CLOCKS_PER_SEC;
                printf("Buborek rendezes: %lf\n",time_taken);

                break;
            case 2:
                t_insertion = clock();
                insertion_sort(arr);
                t_insertion = clock() - t_insertion;
                time_taken = ((double)t_insertion)/CLOCKS_PER_SEC;
                printf("Beszuro rendezes: %lf\n",time_taken);

                break;
            case 3:
                t_heap = clock();
                heap_sort(arr);
                t_heap = clock() - t_heap;
                time_taken = ((double)t_heap)/CLOCKS_PER_SEC;
                printf("Halmaz rendezes: %lf\n",time_taken);

                break;
            case 4:
                t_minselect = clock();
                minselection_sort(arr);
                t_minselect = clock() - t_minselect;
                time_taken = ((double)t_minselect)/CLOCKS_PER_SEC;
                printf("Minimumkivalasztasos rendezes: %lf\n",time_taken);

                break;
        }
    }
    t_all = clock() - t_all;
    time_taken = ((double)t_all)/CLOCKS_PER_SEC;
    printf("A rendezesekhez szukseges ossz ido (parhuzamos eset): %lf\n",time_taken);
    
t_all = clock();
    for(int i = 0;i<5;i++){
        srand(time(NULL));
        fill_array(arr);
        switch(i){
            case 0:
                t_seq = clock();
                quick_sort(arr, 0, ARRAY_SIZE-1);
                t_seq = clock() - t_seq;
                time_taken = ((double)t_seq)/CLOCKS_PER_SEC;
                printf("Gyors rendezes: %lf\n",time_taken);

                break;
            case 1:
                t_seq = clock();
                bubble_sort(arr);
                t_seq = clock() - t_seq;
                time_taken = ((double)t_seq)/CLOCKS_PER_SEC;
                printf("Buborek rendezes: %lf\n",time_taken);

                break;
            case 2:
                t_seq = clock();
                insertion_sort(arr);
                t_seq = clock() - t_seq;
                time_taken = ((double)t_seq)/CLOCKS_PER_SEC;
                printf("Beszuro rendezes: %lf\n",time_taken);

                break;
            case 3:
                t_seq = clock();
                heap_sort(arr);
                t_seq = clock() - t_seq;
                time_taken = ((double)t_seq)/CLOCKS_PER_SEC;
                printf("Halmaz rendezes: %lf\n",time_taken);

                break;
            case 4:
                t_seq = clock();
                minselection_sort(arr);
                t_seq = clock() - t_seq;
                time_taken = ((double)t_seq)/CLOCKS_PER_SEC;
                printf("Minimumkivalasztasos rendezes: %lf\n",time_taken);

                break;
        }
    }
    t_all = clock() - t_all;
    time_taken = ((double)t_all)/CLOCKS_PER_SEC;
    printf("A rendezesekhez szukseges ossz ido (szekvencialis eset): %lf\n",time_taken);

    return 0;
}
