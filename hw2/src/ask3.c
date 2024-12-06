#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

void init_jacobi(int N);
double calc_max_norm(short int **A, short int *b, int N, double *x);
int jacobi(short int **A, short int *b, int N, int maxIter, double tol, double *x);

int main(int argc, char* argv[]){
    int N, maxIter;
    int iter;
    double start, end;
    double max_norm;
    double tol;
    short int **A, *b;
    double *x;
    
    // Get input 
    N = atoi(argv[1]);
    maxIter = atoi(argv[2]);
    tol = atof(argv[3]);

    // Allocate memory for arrays and vectors
    A = (short int **)malloc(N*sizeof(short int *));
    for(int i=0; i<N; i++) {
        A[i] = (short int *)malloc(N*sizeof(short int));
    }
    b = (short int *)malloc(N*sizeof(short int));
    x = (double *)malloc(N*sizeof(double));

    // Initialize A, b and x values
    for (int i=0; i<N; i++){
        b[i] = 0;
        x[i] = 0;
        for (int j=0; j<N; j++){
            if (i==j){
                A[i][j] = 2;
            }
            else if(j==i-1 || j==i+1) {
                A[i][j] = -1;
            }
            else {
                A[i][j] = 0;
            }
        }
    }
    b[N-1] = N+1;
    
    init_jacobi(N);
    printf("Starting Jacobi method with N = %d, max iterations = %d, tolerance = %.8f\n\n", N, maxIter, tol);

    start = omp_get_wtime();
    // Parallel computation
    #pragma omp parallel default(shared) 
    {
        iter = jacobi(A, b, N, maxIter, tol, x);
    }
    end = omp_get_wtime();

    // Calculate max norm
    max_norm = calc_max_norm(A, b, N, x);
    
    
    printf("Jacobi method done.\n\tError = %.6f\n\tTime = %.6f\n", max_norm, end-start);

    return 0;
}