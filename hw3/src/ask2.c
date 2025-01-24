#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include<unistd.h>
int Broadcast(int id, int number, int max_id) {
    double size = log2((double)(max_id + 1));
    if(id==0) MPI_Send(&number, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    if(id==1) MPI_Recv(&number, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    for(int i=1; i<size; i++){
        int partition = (float)(1<<i);
        // if (id==0){
        //     printf("partition=%d\n", partition);
        // }
        
        if ((id < partition) && (id <= max_id) && (id+partition <= max_id)){
            MPI_Send(&number, 1, MPI_INT, (id+partition), 0, MPI_COMM_WORLD);
            //printf("%d)SEND num%d ::: id=%d, to=%d [%d]\n",i, number, id, (id+partition), partition);
        }else if((id >= partition) && (id-partition <= max_id) && (id < 2*partition)){
            //printf("wait id%d from%d\n", id, id-partition);
            MPI_Recv(&number, 1, MPI_INT, (id-partition), 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //printf("RECV num%d ::: id=%d, from=%d  [[%d]]\n",number, id, (id-partition), partition);
        }
        
        //sleep(1);
        //printf("%d\n", id);
        //sleep(1);
        //MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Barrier(MPI_COMM_WORLD);
    return number;
}

int main(int argc, char **argv) {
    int rank, size;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    int number = 0; // broadcasted number
    double start_time, end_time, total_time = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Get_processor_name(processor_name, &name_len);

    if (rank == 0) {
        printf("Processor: %s, Number of tasks = %d\n", processor_name, size);
        printf("Hello. This is the master node.\n");
        number = 4;
    } else {
        printf("Hello. This is node %d.\n", rank);
    }

    //Broadcast from master to all other nodes
    for (int i = 0; i < 1000; i++) {

        MPI_Barrier(MPI_COMM_WORLD);
        start_time = MPI_Wtime(); 

        MPI_Bcast(&number, 1, MPI_INT, 0, MPI_COMM_WORLD); // Broadcast the number to all nodes

        end_time = MPI_Wtime(); 
        total_time += (end_time - start_time);
    }
    double average_time = total_time / 1000;
    number = 0;
    if (rank == 0) {
        printf("Average time for MPI_Bcast with %d tasks: %.8f seconds\n", size, average_time);
        number = 4;
    }
    total_time = 0.0;

    MPI_Barrier(MPI_COMM_WORLD);

    for (int i = 0; i < 1; i++) {
        MPI_Barrier(MPI_COMM_WORLD); // synchronization point
        start_time = MPI_Wtime(); 

        number = Broadcast(rank, number, size-1); // Broadcast the number to all nodes

        end_time = MPI_Wtime(); 
        total_time += (end_time - start_time);
    }
    printf("Node %d received number %d!!!!!!!!\n", rank, number);
    average_time = total_time / 1000;
    if (rank == 0) {
        printf("Average time for Broadcast with %d tasks: %.8f seconds\n", size, average_time);
    }

    MPI_Finalize();
    return 0;
}
