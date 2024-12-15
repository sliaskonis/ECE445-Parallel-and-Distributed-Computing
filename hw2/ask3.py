import subprocess
import os

# Parameters for the C program
N = 10000
iter_ = 200
tol = 0.00005

# Different thread counts to run the program with
thread_counts = [1, 2, 4, 5, 8, 10, 12, 16, 20, 32]

# Create the 'outputs' directory if it doesn't exist
output_dir = "outputs"
if not os.path.exists(output_dir):
    os.makedirs(output_dir)

# Loop through each thread count
for threads in thread_counts:

    # Run the C program with the specific parameters and capture the output
    command = f'./bin/ask3 {N} {iter_} {tol} {threads}'

    # Output file path in the 'outputs' directory
    output_file = os.path.join(output_dir, f'output_{threads}_threads.txt')

    print(f"Running with {threads} threads...")

    # Execute the command and save output to a file in the 'outputs' directory
    with open(output_file, 'w') as f:
        subprocess.run(command, shell=True, stdout=f, stderr=subprocess.PIPE)