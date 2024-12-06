#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define M 10
#define K 10
#define N 10
#define LEVEL 3

int main(int argc, char* argv[]) {
    int A[M][K];
    int B[K][N];
    int C[M][N];
    int id;
    double program_start, program_end;
    double parallel_start, parallel_end;
    double start, end;
    int *nflops;
    double *thread_times;

    int chunk = atoi(argv[1]);
    int n_threads = atoi(argv[2]);
    //int level = atoi(argv[3]);

    program_start = omp_get_wtime();
    omp_set_num_threads(n_threads);
    nflops = (int *)calloc(n_threads, sizeof(int));
    thread_times = (double *)malloc(n_threads*sizeof(double));


    printf("Starting matrix-matrix multiplication example with %d threads, M= %d, K= %d, N= %d, chunk= %d\n", n_threads, M, K, N, chunk);

    #pragma omp parallel private(id, start, end)
    {
        start = omp_get_wtime();
        id = omp_get_thread_num();
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
        
        #pragma omp barrier

        #pragma omp single
            parallel_start = omp_get_wtime();

        printf("Thread %d is starting computations.\n", id);
        // calculate AxB = C

        #pragma omp for schedule(static, chunk) collapse(LEVEL)
            for(int i=0; i<M; i++) {
                for(int j=0; j<N; j++) {
                    for(int k=0; k<K; k++) {
                        printf("Thread=%d did c[i,j] for i =%d , j =%d, and k = %d", id, i, j, k);
                        #pragma omp atomic
                            C[i][j] += A[i][k]*B[k][j];
                        nflops[id]++;
                    }
                }
            }

        end = omp_get_wtime();
        thread_times[id] = end - start;

        #pragma omp barrier

        #pragma omp single
            parallel_end = omp_get_wtime();
    }

    program_end = omp_get_wtime();
    printf("Computations are done.\n");
    printf("***********************************\n");
    printf("Time per thread:\n");
    for(int i=0; i<n_threads; i++) {
        printf("Time for thread %d = %.6f. Number of FLOp = %d\n", i, thread_times[i], nflops[i]);
    }
    printf("Total Parallel Time = %.6f sec.\n", parallel_end - parallel_start);
    printf("Wall Clock Time = %.6f sec.\n", program_end - program_start);
}