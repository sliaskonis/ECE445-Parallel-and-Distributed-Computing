# Parallel & Distributed Computing - Homework 3

## Getting Started
All the implementations of problems 1-4 are stored under the `src` directory. The makefile provided here, will compile all
programs and store their executables in the `bin` directory. Below, there are details about each program and instructions
for their execution.

# Problem 1

The file `ask1.c` contains the code for measuring the the communication overhead of MPI tasks.
You can compile the program using the provided makefile and then execute as:

```bash
mpirun -np <number of processors> ./bin/ask1
```

# Problem 2

The file `ask2.c` contains the implementation of a custom broadcast algorithm using MPI. The program will also execute and compare the algorithm to the MPI_Bcast function. You can compile
the program using the provided makefile and then execute as:

```bash
mpirun -np <number of processors> ./bin/ask2 <numIters>
```
where:
- numIters: the number of iterations each broadcast function will be executed so that a total average time is measured.

# Problem 3

The file `ask3.c` contains an MPI implementation of a matrix-vector multiplication.
You can compile the program using the provided makefile and the execute as:

```bash
mpirun -np <number of processors> ./bin/ask3 <N>
```
where:
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

# Problem 4

The files `ask4_ser.c` and `ask4_par.c` contain a sequential and parallel implementation of the Odd-Even-Transposition algorithm for sorting a sequence of number respectively.
To execute the serial version use:

```bash
./bin/ask4_ser <numNumbers>
```
where:
- numNumbers: the total amount of numbers that will be generated and sorted.

As of the parallel implementation:

```bash
mpirun -np <number of processors> ./bin/ask4_par <numNumbers>
```
