#include <stdio.h>
#include <omp.h>
// compile with :: gcc -g ask1.c -o ask1 -fopenmp

int main(int argc, char* argv[]) {
    double start, end;
    int my_id;


    #pragma omp parallel private(start, end, my_id)
    {
        start = omp_get_wtime();
        my_id = omp_get_thread_num();

        #pragma omp master
        {
            printf("HELLO. I am the Master thread.  I created all participating threads. \n");
        }

        #pragma omp single
        {
            #ifdef _OPENMP
                printf("OpenMP version: %d. Information provided by thread %d .\n", _OPENMP, my_id);
            #else
                printf("No OpenMP support\n");
            #endif
            printf("Number of processors = %d\n", omp_get_num_procs());
            printf("Number of threads = %d\n", omp_get_num_threads());
            printf("Max threads = %d\n", omp_get_max_threads());
            printf("In parallel? = %d\n", omp_in_parallel());
            printf("Dynamic threads enabled? = %d\n", omp_get_dynamic());
            printf("Nested parallelism levels supported = %d\n", omp_get_nested());
        }
        
        end = omp_get_wtime();
        printf("I am thread %d and worked for %.6f msec.\n", my_id, (end-start)*1000); 
    }
}