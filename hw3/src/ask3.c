#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void rowMVMult(int n, double *local_A, double *local_b, double *local_y, int num_tasks, MPI_Comm comm) {
    int rank, size, local_n;

    MPI_Comm_rank(comm, &rank);

    local_n = n / num_tasks; // Numbders of rows each process handles

    // Calculate local y = A * b
    for (int i = 0; i < local_n; i++) {
        local_y[i] = 0.0;
        for (int j = 0; j < n; j++) {
            local_y[i] += local_A[i * n + j] * local_b[j];
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
    int rank, num_tasks, n;
    double *A = NULL, *y = NULL, *b = NULL;
    double *local_A, *local_y, total_time;
    double start_time, end_time;

    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return -1;
    }
    n = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);

    if (n % num_tasks != 0) {
        if (rank == 0) {
            printf("Error: n must be divisible by the number of processes.\n");
        }
        MPI_Finalize();
        return -1;
    }

    int local_n = n / num_tasks; // Number of rows each process will handle

    // Allocate memory for local A, b, y
    local_A = (double *)malloc(local_n * n * sizeof(double));
    local_y = (double *)malloc(local_n * sizeof(double));
    b       = (double *)malloc(n       * sizeof(double));

    if ((b == NULL) || (local_y == NULL) || (local_A == NULL)) {
        fprintf(stderr, "Memory allocation failed\n");
        MPI_Abort(MPI_COMM_WORLD, 1);
    }

    // Data Initialization from master task
    if (rank == 0) {
        A = (double *)malloc(sizeof(double) * n * n);
        y = (double *)malloc(sizeof(double) * n);

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

        // Start timer
        start_time = MPI_Wtime();
    }

    // Send A and b to all processes
    MPI_Scatter(A, local_n * n, MPI_DOUBLE, local_A, local_n * n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Bcast(b, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Each process calculates local y = A * b
    rowMVMult(n, local_A, b, local_y, num_tasks, MPI_COMM_WORLD);

    // Gather all local y's to the master process
    MPI_Gather(local_y, local_n, MPI_DOUBLE, y, local_n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    // Print the resulting vector y
    if (rank == 0) {

        // End timer
        end_time = MPI_Wtime();

        total_time = end_time - start_time;

        // Print the resulting vector y (only for n < 10)
        if (n < 10) {
            printf("Resulting vector y:\n");
            for (int i = 0; i < n; i++) {
                printf("%f ", y[i]);
            }
            printf("\n");
        }

        printf("%f\n", total_time);

        free(A);
        free(y);
    }

    // Cleanup
    free(b);
    free(local_A);
    free(local_y);

    MPI_Finalize();

    return 0;
}
