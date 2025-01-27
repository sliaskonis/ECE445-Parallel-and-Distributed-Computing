#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../include/colours.h"

#define NUM_ITER 1000

void measure_time(int rank, int tag, void *val, MPI_Datatype datatype, const char *datatype_str);

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    if (rank == 0) {
        printf(GRN"Processor: %s, Number of tasks = %d\n"RESET, processor_name, size);
        printf(RED "Hello. This is the master node.\n" RESET);
    } else {
        printf(BLU "Hello. This is node %d.\n" RESET, rank);
    }

    /*
     * Measure time for sending and receiving integers, floats and doubles
     */
    if (rank < 2) {
        int ivalue = rand();
        measure_time(rank, 0, &ivalue, MPI_INT, "MPI_INT");
        float fvalue = rand() / (float)RAND_MAX;
        measure_time(rank, 1, &fvalue, MPI_FLOAT, "MPI_FLOAT");
        double dvalue = rand() / (double)RAND_MAX;
        measure_time(rank, 2, &dvalue, MPI_DOUBLE, "MPI_DOUBLE");
    }

    MPI_Finalize();
    return 0;
}

void measure_time(int rank, int tag, void *val, MPI_Datatype datatype, const char *datatype_str) {
    double start_time, end_time, total_time = 0.0;
    int type_size;
    MPI_Type_size(datatype, &type_size);
    void *recv_val = malloc(type_size);

    for (int i = 0; i < NUM_ITER; i++) {
        if (rank == 0) {
            start_time = MPI_Wtime();
            MPI_Send(val, 1, datatype, 1, tag, MPI_COMM_WORLD);
            MPI_Recv(val, 1, datatype, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            end_time = MPI_Wtime();
            total_time += (end_time - start_time) * 1000000;
        } else if (rank == 1) {
            MPI_Recv(recv_val, 1, datatype, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(recv_val, 1, datatype, 0, tag, MPI_COMM_WORLD);
        }
    }

    if (rank == 0) {
        printf(GRN "Average time for (datatype: %s) = %f μs\n" RESET, datatype_str, total_time / NUM_ITER);
    }
    free(recv_val);
}
