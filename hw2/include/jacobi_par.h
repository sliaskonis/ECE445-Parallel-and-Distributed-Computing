#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

#define _NESTED_
#define N_THREADS 5

void init_jacobi(int N);

double calc_max_norm(short int **A, short int *b, int N, double *x);

int jacobi(short int **A, short int *b, int N, int maxIter, double tol, double *x);