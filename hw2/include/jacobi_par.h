#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

// #define _NESTED_

void init_jacobi(int N);

double calc_error(double *x, double *x_star, int N);

int jacobi(double **A, double *b, int N, int maxIter, double tol, double *x);