#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    int rank, size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    int number = 4; // broadcasted number
    double start_time, end_time, total_time = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name, &name_len);

    printf("Processor %s, rank %d out of %d processors\n", processor_name, rank, size);

    if (rank == 0) {
        printf("Hello. This is the master node.\n");
    } else {
        printf("Hello. This is node %d.\n", rank);
    }

    //Broadcast from master to all other nodes
    for (int i = 0; i < 1000; i++) {
        if (rank == 0) {
            number = i;
        }

        MPI_Barrier(MPI_COMM_WORLD); // synchronization point
        start_time = MPI_Wtime(); 

        MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the number to all nodes

        end_time = MPI_Wtime(); 
        total_time += (end_time - start_time);
    }

    double average_time = total_time / 1000;

    if (rank == 0) {
        printf("Average time for MPI_Bcast with %d tasks: %f seconds\n", size, average_time);
    }

    MPI_Finalize();
    return 0;
}
