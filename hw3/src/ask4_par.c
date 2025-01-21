#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

void compare_exchange(int *n1, int *n2) {
    if(*n1 > *n2) {
        int temp = *n1;
        *n1 = *n2;
        *n2 = temp;
    }
}

void compare_exchange_inverse(int *n1, int *n2) {
    if(*n1 < *n2) {
        int temp = *n1;
        *n1 = *n2;
        *n2 = temp;
    }
}

// odd-even sort
void oddevenser(int *array, int n) {
    for(int i=0; i<n; i++) {
        if(i%2==0) {
            for(int j=0; j<n/2; j++) {
                compare_exchange(&array[2*j], &array[2*j+1]);
            }
        }
        else {
            for(int j=0; j<n/2-1; j++) {
                compare_exchange(&array[2*j+1], &array[2*j+2]);
            }
        }
    }
}

void compare_split(int *array, int n, int *recvarray) {
    int rank, np;
    int *temparray = (int *)malloc(n * sizeof(int));

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    for(int j=0; j<np; j++) {
        if((j%2 == 0)? rank % 2 == 1 : rank % 2 == 0) {
            if(rank < np-1) {
                printf("Rank %d sending array to rank %d\n", rank, rank+1);
                for(int i=0; i<n; i++) {
                    printf("Rank %d \t%d \n", rank, array[i]);
                }
                MPI_Send(array, n, MPI_INT, rank+1, 0, MPI_COMM_WORLD);
                MPI_Recv(recvarray, n, MPI_INT, rank+1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                printf("Rank %d received array from rank %d\n", rank, rank+1);
                for(int i=0; i<n; i++) {
                    printf("Rank %d \t%d \n", rank, recvarray[i]);
                }
                int i = 0, ia = 0, ir = 0;
                for(; i<n; i++) {
                    if(ia == n) {
                        temparray[i] = recvarray[ir];
                        ir++;
                        continue;
                    }
                    else if(ir == n) {
                        temparray[i] = array[ia];
                        ia++;
                        continue;
                    }
                    int flag = array[ia] < recvarray[ir];
                    printf("Rank %d comparing array[%d] = %d and recvarray[%d] = %d, flag = %d\n", rank, ia, array[ia], ir, recvarray[ir], flag);

                    if(flag) {
                        temparray[i] = array[ia];
                        ia++;
                    }
                    else {
                        temparray[i] = recvarray[ir];
                        ir++;
                    }
                }

                for(int i=0; i<n; i++) {
                    array[i] = temparray[i];
                }
                printf("Rank %d updated array: ", rank);
                for(int i=0; i<n; i++) {
                    printf("%d ", array[i]);
                }
                printf("\n");
            }
        }
        else {
            if(rank > 0) {
                printf("Rank %d receiving array from rank %d\n", rank, rank-1);
                MPI_Recv(recvarray, n, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                for(int i=0; i<n; i++) {
                    printf("Rank %d \t%d \n", rank, recvarray[i]);
                }
                MPI_Send(array, n, MPI_INT, rank-1, 0, MPI_COMM_WORLD);
                printf("Rank %d sent array to rank %d\n", rank, rank-1);
                for(int i=0; i<n; i++) {
                    printf("Rank %d \t%d \n", rank, array[i]);
                }
                int ia = n-1, ir = n-1;
                for(int i=n-1; i>=0; i--) {
                    int flag = array[ia] > recvarray[ir];
                    printf("Rank %d comparing array[%d] = %d and recvarray[%d] = %d inversely, flag = %d\n", rank, ia, array[ia], ir, recvarray[ir], flag);

                    if(flag) {
                        temparray[i] = array[ia];
                        ia--;
                    }
                    else {
                        temparray[i] = recvarray[ir];
                        ir--;
                    }
                }

                for(int i=0; i<n; i++) {
                    array[i] = temparray[i];
                }
                printf("Rank %d updated array inversely: ", rank);
                for(int i=0; i<n; i++) {
                    printf("%d ", array[i]);
                }
                printf("\n");
            }
        }
    }
    free(temparray);
}

int main(int argc, char *argv[]) {
    int rank, np;
    int n, localn;
    int *masterarray, *checkarray;
    int *localarray, *recvarray;

    if(argc!=2) {
        printf("Usage: %s <n>\n", argv[0]);
        return -1;
    }

    // a
    n = atoi(argv[1]);
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &np);

    if(n % np != 0) {
        if(rank == 0) {
            printf("Error: n must be divisible by the number of processes.\n");
        }
        MPI_Finalize();
        return -1;
    }

    localn = n / np;

    localarray = (int *)malloc(localn * sizeof(int));
    recvarray = (int *)malloc(localn * sizeof(int));
    if(!rank) { // master process
        masterarray = (int *)malloc(n * sizeof(int));
        checkarray = (int *)malloc(n * sizeof(int));
    }

    // b
    srandom(time(NULL) + rank);

    for(int i=0; i<localn; i++) {
        localarray[i] = (int)random()%10;
        printf("Rank %d: localarray[%d] = %d\n", rank, i, localarray[i]);
    }


    MPI_Gather(localarray, localn, MPI_INT, checkarray, localn, MPI_INT, 0, MPI_COMM_WORLD);

    // c
    oddevenser(localarray, localn);

    // d
    compare_split(localarray, localn, recvarray);

    MPI_Gather(localarray, localn, MPI_INT, masterarray, localn, MPI_INT, 0, MPI_COMM_WORLD);

    if(!rank) {
        oddevenser(checkarray, n);
        for(int i=0; i<n; i++) {
            printf("\t\t\t%11d %11d\n", masterarray[i], checkarray[i]);
            
            //if(masterarray[i] != checkarray[i]) {
            //    printf("Error: Arrays do not match.\n");
            //    break;
            //}
        }
    }

    MPI_Finalize();
    return(0);
}