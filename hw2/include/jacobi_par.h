#ifndef _JAOCBI_PAR_H_
#define _JAOCBI_PAR_H_

#define N_THREADS 8
// #define _NESTED_

void init_jacobi(int N);
double calc_error(double *x, double *x_star, int N);
int jacobi(double **A, double *b, int N, int maxIter, double tol, double *x);

#endif