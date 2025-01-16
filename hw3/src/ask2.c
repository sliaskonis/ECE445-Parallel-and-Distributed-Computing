#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Broadcast(int id, int number, int max_id) {
    if ((id & 1) == 0) {
        if (id < max_id){
            MPI_Send(&number, 1, MPI_INT, (id ^ 1), 0, MPI_COMM_WORLD);
            printf("Node %d sent number %d\n", id, number);
    }
    }
    else {
        if(id < max_id){
            MPI_Recv(&number, 1, MPI_INT, (id ^ 1), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            printf("Node %d received number %d\n", id, number);
        }
    }
}

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

    if (rank == 0) {
        printf("Processor: %s, Number of tasks = %d\n", processor_name, size);
        printf("Hello. This is the master node.\n");
    } else {
        printf("Hello. This is node %d.\n", rank);
    }

    //Broadcast from master to all other nodes
    for (int i = 0; i < 1000; i++) {

        MPI_Barrier(MPI_COMM_WORLD); // synchronization point
        start_time = MPI_Wtime(); 

        MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the number to all nodes

        end_time = MPI_Wtime(); 
        total_time += (end_time - start_time);
    }
    double average_time = total_time / 1000;
    total_time = 0.0;
    if (rank == 0) {
        printf("Average time for MPI_Bcast with %d tasks: %f seconds\n", size, average_time);
    }

    for (int i = 0; i < 1; i++) {
        MPI_Barrier(MPI_COMM_WORLD); // synchronization point
        start_time = MPI_Wtime(); 

        Broadcast(rank, number, size); // Broadcast the number to all nodes

        end_time = MPI_Wtime(); 
        total_time += (end_time - start_time);
    }
    if (rank == 0) {
        printf("Average time for Broadcast with %d tasks: %f seconds\n", size, average_time);
    }
    average_time = total_time / 1000;

    MPI_Finalize();
    return 0;
}
