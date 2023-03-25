#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int main(){
    int edge,edge_3d;
    int node,node_3d;
    FILE* file;
    int counter[11] = {0}; 
    int counter_3d[16] = {0};
    double distance,distance_3d;

    file = fopen("halo.txt","w");

    

    for(int i = 0;i<50;i++){
        node=i*i;
        edge=2*i*i-2*i;
        
        //printf("%d %d\n",node,edge);
        fprintf(file,"%d\t%d\n",node,edge);
        

    }
    
    printf("12 x 12-es racs:\n");
    
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            for (int k = 0; k < 12; k++) {
                for (int l = 0; l < 12; l++) {
                    if (i != k || j != l) { 
                        distance = sqrt(pow(i-k, 2) + pow(j-l, 2)); 
                        int index = (int) distance; 
                        if (index < 11) {
                            counter[index]++; 
                        }
                    }
                }
            }
        }
    }

    // Az eredmények kiírása
    printf("Tavolsag\tDarabszam\n");
    printf("------------------------\n");
    for (int i = 0; i < 11; i++) {
        printf("%d-%d\t\t%d\n", i, i+1, counter[i]);
    }

    for(int i = 0; i < 24 ; i++){
        node_3d =  (i+1)*(i+1)*(i+1);
        edge_3d = 3*i*i*i;
        //printf("%d %d\n",node_3d,edge_3d);
        fprintf(file,"%d\t%d\n",node_3d,edge_3d);
    }

    printf("\n5 x 5 x 5-os racs:\n");

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                for (int l = 0; l < 10; l++) {
                    for (int m = 0; m < 10; m++) {
                        for (int n = 0; n < 10; n++) {
                            if (i != m || j != n || k != l) { 
                                distance_3d = sqrt(pow(i-m, 2) + pow(j-n, 2) + pow(k-l, 2)); 
                                int index = (int) distance_3d; 
                                if (index < 20) {
                                    counter_3d[index]++; 
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    printf("Tavolsag\tDarabszam\n");
    printf("------------------------\n");
    for (int i = 0; i < 16; i++) {
        printf("%d-%d\t\t%d\n", i, i+1, counter_3d[i]);
    }
    
    



   
}