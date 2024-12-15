import subprocess
import os
import csv

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

# List to store results
results = []

# Loop through each thread count
for threads in thread_counts:
    # Run the C program with the specific parameters and capture the output
    command = f'./bin/ask3 {N} {iter_} {tol} {threads}'

    # Output file path in the 'outputs' directory
    output_file = os.path.join(output_dir, f'output_{threads}_threads.txt')

    print(f"Running with {threads} threads...")

    # Execute the command and capture the output
    result = subprocess.run(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    # Print both stdout and stderr for debugging
    stdout_output = result.stdout.decode().strip()
    stderr_output = result.stderr.decode().strip()

    print(f"stdout: {stdout_output}")

    # Try to parse the execution time (assuming it's in stdout)
    try:
        execution_time = float(stdout_output)  # Try parsing from stdout
        results.append([threads, execution_time])  # Store the result
    except ValueError:
        print(f"Error: Couldn't parse the output for {threads} threads.")
        # Optionally, handle stderr or perform further checks

# Write the results to a CSV file
csv_file = "execution_times.csv"
with open(csv_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Threads", "Execution Time (seconds)"])  # Header
    writer.writerows(results)  # Data rows

print(f"Results saved to {csv_file}")