# Parallel & Distributed Computing - Homework 3

## Getting Started

# Problem 3

The file `ask3.c` contains an MPI implementation of a matrix-vector multiplication.
You can compile the program using the provided makefile and the execute as:

```bash
mpirun -np <number of processors> ./bin/ask3 <N>
```

Where:
- Numbers of processors: numbers of processors participating in the matrix-vector calculation. Use `--oversubscribe` flag if you want to use more nodes than supported by your system.
- N: size of the NxN matrix

Under the `scripts` directory there are also two scripts that can be used in order to obtain useful stats from the implemented algorithms. The `ask3.py` script can be executed as:

```bash
python3 ask3.py <iterations>
```

The script executes the algorithm for various combinations of tasks and array sizes. To ensure accurate time measurement, each combination is executed `iteration` times. The results are saved in the `execution_times.csv` file, located in the `results` directory. After obtaining the csv file, the results can be plotted using `ask3_plot.py` script.

```bash
python3 ask3_plot.py <csv file>
```