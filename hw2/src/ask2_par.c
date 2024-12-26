#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <omp.h>
#include "../include/colours.h"

#ifndef LEVEL
#define LEVEL 1 
#endif

#ifndef AQ
#ifndef BQ
#define M 5
#define K 3
#define N 4
#define PRINT
#endif
#endif

#ifdef AQ
#define M 5
#define K 3
#define N 4
#define PRINT
#endif

#ifdef BQ
#define M 50
#define K 10000
#define N 20
#endif

int main(int argc, char* argv[]) {
    int A[M][K];
    int B[K][N];
    int C[M][N];
    int id;
    double program_start, program_end;
    int *nflops;
    double *thread_start_times;
    double *thread_end_times;
    double first_start = DBL_MAX, last_end = 0;

    if (argc != 3){
        printf(RED"Usage: %s <n_threads> <chunk>\n"RESET, argv[0]);
        exit(1);
    }

    int chunk = atoi(argv[2]);
    int n_threads = atoi(argv[1]);

    omp_set_num_threads(n_threads);
    nflops = (int *)calloc(n_threads, sizeof(int));
    thread_start_times = (double *)malloc(n_threads*sizeof(double));
    thread_end_times = (double *)malloc(n_threads*sizeof(double));

    printf(YEL"Starting matrix-matrix multiplication example with %d threads, M = %d, K = %d, N = %d, chunk = %d\n"RESET, n_threads, M, K, N, chunk);

    program_start = omp_get_wtime();
    #pragma omp parallel private(id)
    {
        id = omp_get_thread_num();
        thread_start_times[id] = omp_get_wtime();

        #pragma omp sections
        {
            // init matrices
            #pragma omp section
            {
                #ifdef PRINT
                    printf(BLU"Thread %d initiallizes array A!\n"RESET,id);
                #endif
                
                for(int i=0; i<M; i++) {
                    for(int j=0; j<K; j++) {
                        A[i][j] = i+j;
                    }
                }
            }

            #pragma omp section
            {
                #ifdef PRINT
                    printf(BLU"Thread %d initiallizes array B!\n"RESET,id);
                #endif

                for(int i=0; i<K; i++) {
                    for(int j=0; j<N; j++) {
                        B[i][j] = i*j;
                    }
                }
            }

            #pragma omp section
            {
                #ifdef PRINT
                    printf(BLU"Thread %d initiallizes array C!\n"RESET,id);
                #endif

                for(int i=0; i<M; i++) {
                    for(int j=0; j<N; j++) {
                        C[i][j] = 0;
                    }
                }
            }
        }

        // Wait for all threads to finish initialization
        #pragma omp barrier

        #ifdef PRINT
            printf("Thread %d is starting computations.\n", id);
        #endif

        #pragma omp for schedule(dynamic, chunk) collapse(LEVEL)
        for(int i=0; i<M; i++) {
            for(int j=0; j<N; j++) {
                for(int k=0; k<K; k++) {
                    #ifdef PRINT
                        printf("Thread=%d did c[i,j] for i =%d , j =%d, and k = %d\n", id, i, j, k);
                    #endif

                    #if LEVEL==3
                        #pragma omp atomic
                        C[i][j] += A[i][k]*B[k][j];
                    #endif

                    nflops[id]+=2;
                }
            }
        }

        thread_end_times[id] = omp_get_wtime();
    }

    program_end = omp_get_wtime();
    printf(GRN"Computations are done.\n"RESET);
    printf(GRN"***********************************\n"RESET);
    printf(CYN"Time per thread:\n"RESET);
    for(int i=0; i<n_threads; i++) {
        printf("Time for thread %d = %.6f. Number of FLOPs = %d\n", i, thread_end_times[i] - thread_start_times[i], nflops[i]);
    }

    // Find first start and last end in order to find the total parallel time
    for (int i = 0; i < n_threads; i++) {
        if (thread_start_times[i] < first_start) {
            first_start = thread_start_times[i];
        }
        if (thread_end_times[i] > last_end) {
            last_end = thread_end_times[i];
        }
    }

    printf(MAG"Total Parallel Time = %.6f sec.\n"RESET, last_end - first_start);
    printf(MAG"Wall Clock Time = %.6f sec.\n"RESET, program_end - program_start);
}