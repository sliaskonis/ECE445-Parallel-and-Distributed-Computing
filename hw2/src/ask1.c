#include <stdio.h>
#include <omp.h>
#include "../include/colours.h"

int main(int argc, char* argv[]) {
    double start, end;
    int my_id;


    #pragma omp parallel private(start, end, my_id)
    {
        start = omp_get_wtime();
        my_id = omp_get_thread_num();

        #pragma omp master
        {
            printf(CYN"HELLO. I am the Master thread.  I created all participating threads. \n"RESET);
        }

        #pragma omp single
        {
            #ifdef _OPENMP
                printf(GRN"OpenMP version: %d. Information provided by thread %d .\n"RESET, _OPENMP, my_id);
            #else
                printf(RED"No OpenMP support\n"RESET);
            #endif
            printf(BLU"Number of processors = %d\n"RESET, omp_get_num_procs());
            printf(BLU"Number of threads = %d\n"RESET, omp_get_num_threads());
            printf(BLU"Max threads = %d\n"RESET, omp_get_max_threads());
            printf(BLU"In parallel? = %d\n"RESET, omp_in_parallel());
            printf(BLU"Dynamic threads enabled? = %d\n"RESET, omp_get_dynamic());
            printf(BLU"Nested parallelism levels supported = %d\n"RESET, omp_get_max_active_levels());
        }

        end = omp_get_wtime();
        printf(CYN"I am thread %d and worked for %.6f msec.\n"RESET, my_id, (end-start)*1000);
    }
}