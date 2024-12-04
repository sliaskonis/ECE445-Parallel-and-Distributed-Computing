#include <stdio.h>
#include <time.h>
#include "../include/norms.h"

/******************************************************************************
 *                                                                            *
 *  File:       library_name.c                                                *
 *  Description:                                                              *
 *      This file contains the implementation of multiple functions for the   *
 *      norms.h library. The norms.h library provides a set of functions for  *
 *      calculating the 1st and max norm of an nxn matrix. For each type of   *
 *      norm, there is a base function plus four more functions that do the   *
 *      same calculations but with different steps (unrolled loops with       *
 *      factors of 2, 4, 8 and 16). All functions take as inputs a float      *  
 *      matrix, the size n of the matrix, and a Norms struct with two fields. *
 *      A float value holding the value of the norm and a double              *  
 *      execution_time variable that keeps track of the execution time of     *
 *      the function.                                                         *
 *                                                                            *
 *     Usage:                                                                 *
 *      The functions follow the naming convention:                           *
 *         find_<norm_type>_step_<step_size>                                  * 
 *                                                                            *
 ******************************************************************************/


/**************************************** 1st Norm Calculation ****************************************/
void find_firstNorm_step_1(float **arr, int n, norms *firstNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int j = 0; j < n; j++) {
        float sum = 0;
        for (int i = 0; i < n; i++) {
            sum += arr[i][j];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    firstNorm->value = max;
    firstNorm->time = cpu_time_used;
}

void find_firstNorm_step_2(float **arr, int n, norms *firstNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int j = 0; j < n; j++) {
        float sum = 0;
        for (int i = 0; i < n; i+=2) {
            sum += arr[i][j];
            sum += arr[i+1][j];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    firstNorm->value = max;
    firstNorm->time = cpu_time_used;
}

void find_firstNorm_step_4(float **arr, int n, norms *firstNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int j = 0; j < n; j++) {
        float sum = 0;
        for (int i = 0; i < n; i+=4) {
            sum += arr[i][j];
            sum += arr[i+1][j];
            sum += arr[i+2][j];
            sum += arr[i+3][j];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    firstNorm->value = max;
    firstNorm->time = cpu_time_used;
}

void find_firstNorm_step_8(float **arr, int n, norms *firstNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int j = 0; j < n; j++) {
        float sum = 0;
        for (int i = 0; i < n; i+=8) {
            sum += arr[i][j];
            sum += arr[i+1][j];
            sum += arr[i+2][j];
            sum += arr[i+3][j];
            sum += arr[i+4][j];
            sum += arr[i+5][j];
            sum += arr[i+6][j];
            sum += arr[i+7][j];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    firstNorm->value = max;
    firstNorm->time = cpu_time_used;
}

void find_firstNorm_step_16(float **arr, int n, norms *firstNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int j = 0; j < n; j++) {
        float sum = 0;
        for (int i = 0; i < n; i+=16) {
            sum += arr[i][j];
            sum += arr[i+1][j];
            sum += arr[i+2][j];
            sum += arr[i+3][j];
            sum += arr[i+4][j];
            sum += arr[i+5][j];
            sum += arr[i+6][j];
            sum += arr[i+7][j];
            sum += arr[i+8][j];
            sum += arr[i+9][j];
            sum += arr[i+10][j];
            sum += arr[i+11][j];
            sum += arr[i+12][j];
            sum += arr[i+13][j];
            sum += arr[i+14][j];
            sum += arr[i+15][j];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    firstNorm->value = max;
    firstNorm->time = cpu_time_used;
}

/**************************************** Max Norm Calculation ****************************************/
void find_maxNorm_step_1(float **arr, int n, norms *maxNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j++) {
            sum += arr[i][j];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    maxNorm->value = max;
    maxNorm->time = cpu_time_used;
}

void find_maxNorm_step_2(float **arr, int n, norms *maxNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j+=2) {
            sum += arr[i][j];
            sum += arr[i][j+1];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    maxNorm->value = max;
    maxNorm->time = cpu_time_used;
}

void find_maxNorm_step_4(float **arr, int n, norms *maxNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j+=4) {
            sum += arr[i][j];
            sum += arr[i][j+1];
            sum += arr[i][j+2];
            sum += arr[i][j+3];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    maxNorm->value = max;
    maxNorm->time = cpu_time_used;
}

void find_maxNorm_step_8(float **arr, int n, norms *maxNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j+=8) {
            sum += arr[i][j];
            sum += arr[i][j+1];
            sum += arr[i][j+2];
            sum += arr[i][j+3];
            sum += arr[i][j+4];
            sum += arr[i][j+5];
            sum += arr[i][j+6];
            sum += arr[i][j+7];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    maxNorm->value = max;
    maxNorm->time = cpu_time_used;
}


void find_maxNorm_step_16(float **arr, int n, norms *maxNorm) {
    float max = 0;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < n; i++) {
        float sum = 0;
        for (int j = 0; j < n; j+=16) {
            sum += arr[i][j];
            sum += arr[i][j+1];
            sum += arr[i][j+2];
            sum += arr[i][j+3];
            sum += arr[i][j+4];
            sum += arr[i][j+5];
            sum += arr[i][j+6];
            sum += arr[i][j+7];
            sum += arr[i][j+8];
            sum += arr[i][j+9];
            sum += arr[i][j+10];
            sum += arr[i][j+11];
            sum += arr[i][j+12];
            sum += arr[i][j+13];
            sum += arr[i][j+14];
            sum += arr[i][j+15];
        }
        if (sum > max) {
            max = sum;
        }
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    maxNorm->value = max;
    maxNorm->time = cpu_time_used;
}
