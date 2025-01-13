#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void rowMVMult(int n, double *localA, double *localb, double *localy, MPI_Comm comm) {
    int rank, size, local_n;

    MPI_Comm_rank(comm, &rank);
    MPI_Comm_size(comm, &size);

    local_n = n / size; // numbders of rows each process handles

    // calculate local y = A * b
    for (int i = 0; i < local_n; i++) {
        localy[i] = 0.0;
        for (int j = 0; j < n; j++) {
            localy[i] += localA[i * n + j] * localb[j];
            //printf("localy[%d]=%f\n",j,localy[i]);
        }
    }

}

void printA(double* A, int n, int local_n){
    for (int i = 0; i < local_n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f ",A[i * n + j]);
        }
        printf("\n");
    }
}

int main(int argc, char **argv) {
    int rank, tasks, n = 4; 
    double *A = NULL, *y = NULL, *b=NULL;
    double *localA, *localb, *localy;
    int local_n;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &tasks);

    if (n % tasks != 0) {
        if (rank == 0) {
            printf("Error: n must be divisible by the number of processes.\n");
        }
        MPI_Finalize();
        return -1;
    }

    local_n = n / tasks; // lines per process
    //printf ("localn=%d, n=%d\n",local_n, n);
    localA = (double *)malloc(local_n * n * sizeof(double));
    localb = (double *)malloc(local_n * sizeof(double));
    localy = (double *)malloc(local_n * sizeof(double));
    if ((localb == NULL) || (localy == NULL) || (localA == NULL)) {
        fprintf(stderr, "Memory allocation failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }
    // a) initialization of A and b by the master
    if (rank == 0) {
        A = (double *)malloc(n * n * sizeof(double));
        b = (double *)malloc(n * sizeof(double));
        y = (double *)malloc(n * sizeof(double));
        if ((A == NULL) || (y == NULL)) {
            fprintf(stderr, "Memory allocation failed\n");
            MPI_Abort(MPI_COMM_WORLD, 1);
        }
        for (int i = 0; i < n; i++) {
            b[i] = 10.0;
            for (int j = 0; j < n; j++) {
                A[i * n + j] = (i + j) * 10.0;
            }
        }
    }
    // b) and c) scatter A to all processes && broadcast b to all processes
    MPI_Scatter(A, local_n * n, MPI_DOUBLE, localA, local_n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Scatter(b, local_n, MPI_DOUBLE, localb, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // d) calculation of local y = A * b
    rowMVMult(n, localA, localb, localy, MPI_COMM_WORLD);

    // e) gather local y to the master
    MPI_Gather(localy, local_n, MPI_DOUBLE, y, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // f) print the resulting vector y
    if (rank == 0) {
        printf("Resulting vector y:\n");
        for (int i = 0; i < n; i++) {
            printf("%f ", y[i]);
        }
        printf("\n");
        free(A);
        free(b);
        free(y);
    }
    free(localA);
    free(localb);
    free(localy);

    MPI_Finalize();
    return 0;
}
