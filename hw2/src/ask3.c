#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>
#include "../include/jacobi_par.h"
#include "../include/colours.h"

void init_system (double ***A, double **b, double **x, int N){

    *A = (double **)malloc(N * sizeof(double *));
    *b = (double *) malloc(N * sizeof(double));
    *x = (double *) malloc(N * sizeof(double));
    for (int i=0; i<N; i++){
        (*A)[i] = (double *)malloc(N * sizeof(double));
    }

    // Initialize A, b and x values
    for (int i=0; i<N; i++){
        (*b)[i] = 0;
        (*x)[i] = 0;
        for (int j=0; j<N; j++){
            if (i==j){
                (*A)[i][j] = 2;
            }
            else if(j==i-1 || j==i+1) {
                (*A)[i][j] = -1;
            }
            else {
                (*A)[i][j] = 0;
            }
        }
    }
    (*b)[N-1] = N+1;
}

void free_system (double ***A, double **b, double **x, int N){

    for (int i=0; i<N; i++){
        free((*A)[i]);
    }
    free(*A);
    free(*b);
    free(*x);
}

int main(int argc, char* argv[]){
    int N, maxIter;
    int iter;
    double start, end;
    double max_norm;
    double tol;
    double **A, *b;
    double *x, *x_star;

#ifdef _NESTED_
    omp_set_max_active_levels(2);
#endif

    if (argc != 4){
        printf(RED"Usage: %s <N> <maxIter> <tol>\n"RESET, argv[0]);
        exit(1);
    }

    // Get input
    N = atoi(argv[1]);
    maxIter = atoi(argv[2]);
    tol = atof(argv[3]);

    // Set number of threads
    omp_set_num_threads(N_THREADS);

    // Initialize x_star
    x_star = (double *)malloc(N*sizeof(double));
    for (int i=0; i<N; i++){
        x_star[i] = i+1;
    }

    // Initialize A, b and x values
    init_system(&A, &b, &x, N);

    // Initialize Jacobi method
    init_jacobi(N);

    printf(GRN"Starting Jacobi method with N = %d, max iterations = %d, tolerance = %.8f, # of threads = %d\n\n"RESET, N, maxIter, tol, N_THREADS);

    start = omp_get_wtime();
    #pragma omp parallel num_threads(N_THREADS) default(shared)
    {
        iter = jacobi(A, b, N, maxIter, tol, x);
    }
    end = omp_get_wtime();

    // Calculate max norm
    max_norm = calc_error(x, x_star, N);

    // Print results
    printf(GRN"Jacobi method done.\n"RESET);
    printf(RED"\tError = %.6f\n"RESET, max_norm);
    printf(GRN"\tTime = %.6f sec\n"RESET, end-start);

    // Cleanup
    free_system(&A, &b, &x, N);
    free(x_star);

    return 0;
}