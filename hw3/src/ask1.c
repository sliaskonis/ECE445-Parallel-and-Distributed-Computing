#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_ITER 1000

void measure_time(int rank, int tag, void* val, MPI_Datatype datatype) {
    double start_time, end_time, total_time = 0.0;

    for (int i = 0; i < NUM_ITER; i++) {
        if (rank == 0) {
            start_time = MPI_Wtime();
            MPI_Send(&val, 1, datatype, 1, tag, MPI_COMM_WORLD);
            MPI_Recv(&val, 1, datatype, 1, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            end_time = MPI_Wtime();
            total_time += (end_time - start_time);
        } else if (rank == 1) {
            MPI_Recv(&val, 1, datatype, 0, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Send(&val, 1, datatype, 0, tag, MPI_COMM_WORLD);
        }
    }
    // στ
    if (rank == 0) {
        char* datatype_str = datatype == MPI_INT ? "int" : datatype == MPI_FLOAT ? "float" : "double";
        printf("Average time for (datatype: %s) = %f seconds\n",
               datatype_str,
               total_time / NUM_ITER);
    }
}

int main(int argc, char **argv) {
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // a
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    //b
    if (rank == 0) {
        printf("Processor: %s, Number of tasks = %d\n", processor_name, size);
        printf("Hello. This is the master node.\n");
    } else {
        printf("Hello. This is node %d.\n", rank);
    }

    // c, d, e
    if (rank < 2) {
        int ivalue = 1;
        measure_time(rank, 0, &ivalue, MPI_INT);
        float fvalue = 1.0;
        measure_time(rank, 1, &fvalue, MPI_FLOAT);
        double dvalue = 1.0;
        measure_time(rank, 2, &dvalue, MPI_DOUBLE);
    }

    MPI_Finalize();
    return 0;
}
