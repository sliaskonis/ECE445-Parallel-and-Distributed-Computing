#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define DEBUG
#define SEED 42

// compare and exchange two integers
void compare_exchange(int *n1, int *n2) {
    if(*n1 > *n2) {
        int temp = *n1;
        *n1 = *n2;
        *n2 = temp;
    }
}

// odd-even sort
void oddevenser(int *array, int n) {
    for(int i=1; i<=n; i++) {
#ifdef DEBUG
        printf("Iteration %d: ", i);
        for(int k=0; k<n; k++) {
            printf("%d ", array[k]);
        }
        printf("\n");
#endif

        if(i%2==1) { // odd
            for(int j=0; j<n/2; j++) {
                compare_exchange(&array[2*j], &array[2*j+1]);
            }
        }
        else { // even
            for(int j=0; j<n/2-1; j++) {
                compare_exchange(&array[2*j+1], &array[2*j+2]);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n;
    int *array;
    clock_t start, end;

    if(argc!=2) {
        printf("Usage: %s <n>\n", argv[0]);
        return -1;
    }

    // get n
    n = atoi(argv[1]);

    array = (int *)malloc(n * sizeof(int));

    // seed random number generator
    srandom(SEED);

    // initialize array with random values
    for(int i=0; i<n; i++) {
        array[i] = random()%100;
    }

#ifdef DEBUG
    // print initial array
    printf("Initial array: ");
    for(int i=0; i<n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
#endif

    // start timer
    start = clock();

    // sort array
    oddevenser(array, n);

    // end timer
    end = clock();

#ifdef DEBUG
    // print sorted array
    printf("Sorted array: ");
    for(int i=0; i<n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
#endif

    // print elapsed time
    printf("Elapsed time: %f seconds\n", (double)(end - start) / CLOCKS_PER_SEC);

    free(array);

    return 0;
}