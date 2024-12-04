#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

// returns num of iterations
int jacobi(double **A, double *b, int N, int maxIter, int tol, double *x) {
    int iter = 0;
    double sum;
    double res[N];
    double x_k[N];
    double maxnorm_res, maxnorm_calc;
    
    while(iter < maxIter) {

        for(int i=0; i<N; i++) {
            sum = A[i][i]*x[i];
            
            for(int j=0; j<N; j++) {
                sum -= A[i][j]*x[j];
            }
            x_k[i] = (b[i] + sum)/A[i][i];
        }

        // max norm of residual 
        for(int i=0; i<N; i++) {
            res[i] = b[i];
            for(int j=0; j<N; j++) {
                res[i] -= A[i][j]*x_k[j];
            }
        }

        maxnorm_res = fabs(res[0]);
        for(int i=1; i<N; i++) 
            if(maxnorm_res < fabs(res[i]))
                maxnorm_res = fabs(res[i]);
        
        maxnorm_calc = 0;
        for(int i; i<N; i++) {
            res[i] = fabs(x[i]-x_k[i]);
            if(maxnorm_calc < res[i])
                maxnorm_calc = res[i];
        }

        printf("iter = %d, residual = %.6f, difference %.6f", iter, maxnorm_res, maxnorm_calc);

        for(int i; i<N; i++) {
            x[i] = x_k[i];
        }

        iter++;
        
    }
}

int main(int argc, char* argv){
    int N = atoi(argv[0]);
    int maxIter = atoi(argv[1]);
    int tol = atoi(argv[2]);

    int error, A[N][N], b[N];

    for (int i=0; i<N; i++){
        b[i]=0;
        for (int j=0; j<N; j++){
            if (i==j){
                A[i][j]=2;
            }
            else{
                A[i][j]=-1;
            }
        }
    }

    error = jacobi();
}