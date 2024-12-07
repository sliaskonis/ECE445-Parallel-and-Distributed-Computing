#include "../include/jacobi_par.h"

double maxnorm_res, maxnorm_calc;
double *res, *x_k;

void init_jacobi(int N) {
    x_k = (double *)malloc(N*sizeof(double));
    res = (double *)malloc(N*sizeof(double));
    maxnorm_res = maxnorm_calc = 0;
}

double calc_max_norm(short int **A, short int *b, int N, double *x) {
    double max_norm = 0;

    for(int i=0; i<N; i++) {
        res[i] = b[i];
        for(int j=0; j<N; j++) {
            res[i] -= A[i][j]*x[j];
        }
        if(fabs(res[i]) > max_norm)
            max_norm = fabs(res[i]);
    }
    return(max_norm);
}

// returns num of iterations
int jacobi(short int **A, short int *b, int N, int maxIter, double tol, double *x) {
    int iter = 0;
    double sum;
    extern double *res, *x_k;
    extern double maxnorm_res, maxnorm_calc;
    int id = omp_get_thread_num();
    
    while(iter < maxIter) {

#ifndef _NESTED_
        #pragma omp for private(sum) 
#else
        #pragma omp parallel for num_threads(N_THREADS) private(sum)
#endif
        for(int i=0; i<N; i++) {
            sum = A[i][i]*x[i];
            
            for(int j=0; j<N; j++) {
                sum -= A[i][j]*x[j];
            }
            x_k[i] = (b[i] + sum)/A[i][i];
            //printf("Thread %d, x_k[%d] = %.6f, A[i][i] = %.6f, b[i] = %.6f\n", id, i, x_k[i], A[i][i], b[i]);
        }

        // max norm of residual 
        #pragma omp for
        for(int i=0; i<N; i++) {
            res[i] = b[i];
            for(int j=0; j<N; j++) {
                res[i] -= A[i][j]*x_k[j];
            }
            //printf("Thread %d, res[%d] = %.6f, b[i] = %.6f\n", id, i, res[i], b[i]);
        }
        #pragma omp single
            maxnorm_res = 0;

        #pragma omp for reduction(max: maxnorm_res)
        for(int i=0; i<N; i++) 
            if(maxnorm_res < fabs(res[i]))
                maxnorm_res = fabs(res[i]);

        /*#pragma omp single 
        {
            printf("\nres = [");
            for(int i=0; i<N; i++) {
                printf(" %.2f", res[i]);
            }
            printf("]\nMax norm = %.6f\n", maxnorm_res);
        }*/
        #pragma omp single
            maxnorm_calc = 0;

        #pragma omp for reduction(max: maxnorm_calc)
        for(int i=0; i<N; i++) {
            res[i] = fabs(x[i]-x_k[i]);
            if(maxnorm_calc < res[i])
                maxnorm_calc = res[i];
        }

        /*#pragma omp single 
        {
            printf("x_k = [");
            for(int i=0; i<N; i++) {
                printf(" %.2f", x[i]);
            }
            printf("]\n");
            printf("x_k+1 = [");
            for(int i=0; i<N; i++) {
                printf(" %.2f", x_k[i]);
            }
            printf("]\n");
        }*/

        #pragma omp for
        for(int i=0; i<N; i++) {
            x[i] = x_k[i];
        }

        #pragma omp single 
            printf("iter = %d, residual = %.6f, difference %.6f\n", iter, maxnorm_res, maxnorm_calc);
            
        iter++; 
            
        #pragma omp barrier
        if(tol > maxnorm_res) 
            break;
    }

    return(iter);
}