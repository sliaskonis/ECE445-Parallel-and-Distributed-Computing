#include "../include/jacobi_par.h"

double maxnorm_res, maxnorm_calc;
double *res, *x_k;

// returns num of iterations
int jacobi(double **A, double *b, int N, int maxIter, double tol, double *x) {
    int iter = 0, id;
    double sum;

    // Get thread id
    id = omp_get_thread_num();

    while(iter < maxIter) {

#ifndef _NESTED_
        #pragma omp for private(sum)
#else
        #pragma omp parallel for private(sum)
#endif
        for(int i = 0; i < N; i++) {
            sum = A[i][i] * x[i];

            for(int j = 0; j < N; j++) {
                sum -= A[i][j] * x[j];
            }
            x_k[i] = (b[i] + sum) / A[i][i];
            // printf("Thread %d, x_k[%d] = %.6f, A[i][i] = %.6f, b[i] = %.6f\n", id, i, x_k[i], A[i][i], b[i]);
        }

        // Calculate residual
        #pragma omp for
        for(int i = 0; i < N; i++) {
            res[i] = b[i];
            for(int j = 0; j < N; j++) {
                res[i] -= A[i][j] * x_k[j];
            }
            //printf("Thread %d, res[%d] = %.6f, b[i] = %.6f\n", id, i, res[i], b[i]);
        }
        #pragma omp single
            maxnorm_res = 0;

        // Calculate max norm of residual
        #pragma omp for reduction(max: maxnorm_res)
        for(int i = 0; i < N; i++)
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
            double diff = fabs(x[i]-x_k[i]);
            if(maxnorm_calc < diff)
                maxnorm_calc = diff;
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

       // Update x with x_k
        #pragma omp for
        for(int i=0; i<N; i++) {
            x[i] = x_k[i];
        }

        // #pragma omp single
        //     printf("iter = %d, residual = %.6f, difference %.6f\n", iter, maxnorm_res, maxnorm_calc);

        iter++;

        #pragma omp barrier
        if(tol > maxnorm_res)
            break;
    }

    return(iter);
}

void init_jacobi(int N) {
    x_k = (double *)malloc(N*sizeof(double));
    res = (double *)malloc(N*sizeof(double));
    maxnorm_calc = 0;
    maxnorm_res  = 0;
}

void destroy_jacobi() {
    free(x_k);
    free(res);
}

double calc_error(double *x, double *x_star, int n) {
    double max_norm = 0;

    for (int i = 0; i < n; i++) {
        double diff = fabs(x_star[i] - x[i]);
        if (max_norm < diff) {
            max_norm = diff;
        }
    }

    return max_norm;
}