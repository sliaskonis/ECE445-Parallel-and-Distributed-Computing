#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/norms.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Usage: %s <array size>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    norms firstNorm;

    /******* Create the array *******/
    float **arr = (float **)malloc(n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        arr[i] = (float *)malloc(n * sizeof(float));
        for (int j = 0; j < n; j++) {
            arr[i][j] = 1.0;
        }
    }

    // Test all fistNorm calculation functions and print the execution times
    find_firstNorm_step_1(arr, n, &firstNorm);
    printf("%f\n", firstNorm.time);

    find_firstNorm_step_2(arr, n, &firstNorm);
    printf("%f\n", firstNorm.time);

    find_firstNorm_step_4(arr, n, &firstNorm);
    printf("%f\n", firstNorm.time);

    find_firstNorm_step_8(arr, n, &firstNorm);
    printf("%f\n", firstNorm.time);

    find_firstNorm_step_16(arr, n, &firstNorm);
    printf("%f\n", firstNorm.time);

    // Free the array
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}