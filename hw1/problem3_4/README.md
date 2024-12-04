# Parallel & Distributed Computing - Homework 1

This project contains implementations for the following matrix norm calculations:

- **Problem 3**: Calculation of the 1-Norm of an \( n \times n \) matrix
- **Problem 4**: Calculation of the Max-Norm of an \( n \times n \) matrix

The project includes a script to compile and run these programs with various matrix sizes and save the execution times. Visualization scripts are also provided to analyze performance results.

## Getting Started

### Prerequisites

- **C Compiler**: Ensure you have a C compiler (like `gcc`) to compile the provided code.
- **Python 3**: The visualization scripts require Python 3 and the following libraries:
  - `matplotlib`
  - `numpy`

### Executing the Code

A shell script, run_all.sh, is provided to compile and execute both Problem 3 and Problem 4 code. This script will run the programs multiple times with different matrix sizes.

Run the script with
```bash
    bash run_all.sh
```
The script will create a results subdirectory where the execution times of each program will be saved. Files in this directory will contain the execution time data for each norm calculation and matrix size.

### Visualizing Results

Two python scripts are available for visualizing the results:
- bar.py: Generates a bar graph showing the mean execution time for each problem with error bars representing standard deviation
- create_graph.py: Generates line plots showcasing how execution times change with varying step sizes for different matrix sizes. Seperate plots are generated for each matrix size.

To generate visualizations, execute the scripts as follows:

```bash
    python bar.py <output_file>
```
or
```bash
    python create_graphs.py <output_file>
```
