#include <stdio.h>
#include <omp.h>
#define M 10
#define K 10
#define N 10
// compile with :: gcc -g ask1.c -o ask1 -fopenmp

int main(int argc, char* argv) {
    int A[M][K];
    int B[K][N];
    int C[M][N];

    // init matrices
    for(int i=0; i<M; i++) {
        for(int j=0; j<K; j++) {
            A[i][j] = i+j;
        }
    } 
    for(int i=0; i<K; i++) {
        for(int j=0; j<N; j++) {
            B[i][j] = i*j;
        }
    } 
    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
            C[i][j] = 0;
        }
    } 
    // calculate AxB = C
    for(int i=0; i<M; i++) {
        for(int j=0; j<N; j++) {
            for(int k=0; k<K; k++) {
                C[i][j] += A[i][k]*B[k][j];
            }
        }
    } 
}