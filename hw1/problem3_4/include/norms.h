#ifndef NORMS_H
#define NORMS_H

typedef struct {
    float value;
    double time; 
} norms;

extern void find_firstNorm_step_1(float **arr, int n, norms *firstNorm);
extern void find_firstNorm_step_2(float **arr, int n, norms *firstNorm);
extern void find_firstNorm_step_4(float **arr, int n, norms *firstNorm);
extern void find_firstNorm_step_8(float **arr, int n, norms *firstNorm);
extern void find_firstNorm_step_16(float **arr, int n, norms *firstNorm);
extern void find_maxNorm_step_1(float **arr, int n, norms *maxNorm);
extern void find_maxNorm_step_2(float **arr, int n, norms *maxNorm);
extern void find_maxNorm_step_4(float **arr, int n, norms *maxNorm);
extern void find_maxNorm_step_8(float **arr, int n, norms *maxNorm);
extern void find_maxNorm_step_16(float **arr, int n, norms *maxNorm);

#endif