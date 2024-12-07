#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <omp.h>
#define M 100
#define K 10000
#define N 20
#define LEVEL 2

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

    int chunk = atoi(argv[2]);
    int n_threads = atoi(argv[1]);

    omp_set_num_threads(n_threads);
    nflops = (int *)calloc(n_threads, sizeof(int));
    thread_start_times = (double *)malloc(n_threads*sizeof(double));
    thread_end_times = (double *)malloc(n_threads*sizeof(double));

    printf("Starting matrix-matrix multiplication example with %d threads, M= %d, K= %d, N= %d, chunk= %d\n", n_threads, M, K, N, chunk);
    printf("chunk=%d, threads:%d\n",chunk,n_threads);

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
                printf("Thread %d initiallizes array A!\n",id);
                for(int i=0; i<M; i++) {
                    for(int j=0; j<K; j++) {
                        A[i][j] = i+j;
                    }
                }
            }

            #pragma omp section
            {
                printf("Thread %d initiallizes array B!\n",id);
                for(int i=0; i<K; i++) {
                    for(int j=0; j<N; j++) {
                        B[i][j] = i*j;
                    }
                }
            }

            #pragma omp section
            {
                printf("Thread %d initiallizes array C!\n",id);
                for(int i=0; i<M; i++) {
                    for(int j=0; j<N; j++) {
                        C[i][j] = 0;
                    }
                }
            }
        }

        // Wait for all threads to finish initialization
        #pragma omp barrier

        printf("Thread %d is starting computations.\n", id);

        #pragma omp for schedule(dynamic, chunk) collapse(LEVEL)
        for(int i=0; i<M; i++) {
            for(int j=0; j<N; j++) {
                for(int k=0; k<K; k++) {
                    //printf("Thread=%d did c[i,j] for i =%d , j =%d, and k = %d\n", id, i, j, k);
                    C[i][j] += A[i][k]*B[k][j];
                    nflops[id]+=2;
                }
            }
        }

        thread_end_times[id] = omp_get_wtime();
    }

    program_end = omp_get_wtime();
    printf("Computations are done.\n");
    printf("***********************************\n");
    printf("Time per thread:\n");
    for(int i=0; i<n_threads; i++) {
        printf("Time for thread %d = %.6f. Number of FLOp = %d\n", i, thread_end_times[i] - thread_start_times[i], nflops[i]);
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

    printf("Total Parallel Time = %.6f sec.\n", last_end - first_start);
    printf("Wall Clock Time = %.6f sec.\n", program_end - program_start);
}