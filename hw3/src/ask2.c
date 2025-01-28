#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include "../include/colours.h"

/* Custom implementation of MPI_Bcast */
int custom_broadcast(int id, int number, int max_id) {
	int recv_id = 1;

	if (id == 0) {
		for (int i = 0; i < max_id; i++) {
			MPI_Send(&number, 1, MPI_INT, recv_id, 0, MPI_COMM_WORLD);
			recv_id++;
		}
	} else {
		MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	}

	MPI_Barrier(MPI_COMM_WORLD);

    return number;
}

int main(int argc, char **argv) {
    double start_time, end_time, mpi_time = 0.0, custom_time = 0.0;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int rank, num_tasks;
    int name_len;
    int number = rand() % 100;
	int num_iters = atoi(argv[1]);

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_tasks);
    MPI_Get_processor_name(processor_name, &name_len);

    if (rank == 0) {
        printf(GRN "Processor: %s, Number of tasks = %d\n" RESET, processor_name, num_tasks);
        printf(GRN "Hello. This is the master node.\n" RESET);
    } else {
        printf(YEL "Hello. This is node %d.\n" RESET, rank);
    }

    /**************** MPI Broadcast *****************/
    for (int i = 0; i < num_iters; i++) {
        MPI_Barrier(MPI_COMM_WORLD);

        start_time = MPI_Wtime();
        MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD);
        end_time = MPI_Wtime();

		mpi_time += (end_time - start_time) * 1000000;
    }

    MPI_Barrier(MPI_COMM_WORLD);

    /**************** Custom Broadcast *****************/
    for (int i = 0; i < num_iters; i++) {
        MPI_Barrier(MPI_COMM_WORLD);

		start_time = MPI_Wtime();
        number = custom_broadcast(rank, number, num_tasks - 1);
        end_time = MPI_Wtime();

		custom_time += (end_time - start_time) * 1000000;
    }

    /**************** Print Final Results *****************/
    if (rank == 0) {
        printf(GRN "Average time for MPI_Bcast with %d tasks:        %f μs\n" RESET, num_tasks, mpi_time / 1000);
        printf(GRN "Average time for custom broadcast with %d tasks: %f μs\n" RESET, num_tasks, custom_time / 1000);
    }

	printf(YEL "Node: %d, received number %d.\n" RESET, rank, number);

    MPI_Finalize();
    return 0;
}
