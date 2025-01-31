import subprocess
import sys
import csv
import os
import re

# Function to remove ANSI escape sequences
def remove_ansi_codes(text):
    ansi_escape = re.compile(r'\x1B(?:[@-Z\\-_]|\[[0-?]*[ -/]*[@-~])')
    return ansi_escape.sub('', text)

if len(sys.argv) != 2:
    print("Usage: python ask3.py <iterations>")
    exit(1)

# Define number of iterations each implementation will be executed
iterations = int(sys.argv[1])
num_tasks = [2, 4, 6, 8, 10, 12, 20]

# Path to the executable
exec_path = "../bin/ask2"

# Output CSV file
output_dir = "../results/ask2"
output_file = os.path.join(output_dir, "execution_times.csv")

# Ensure the 'results' directory exists
os.makedirs(output_dir, exist_ok=True)

# Open the CSV file and write the header
with open(output_file, mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Num_Processors", "MPI_Execution_Time", "Custom_Execution_Time"])

    # Iterate over all combinations of parameters
    for tasks in num_tasks:
            mpi_command = ["mpirun", "-np", str(tasks), "--oversubscribe", exec_path, str(iterations)]
            try:
                # Call the script with the specified arguments
                result = subprocess.run(mpi_command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)

                clean_output = remove_ansi_codes(result.stdout)

                # Split the output into lines
                output_lines = clean_output.splitlines()
                float_values = [float(line) for line in output_lines]

                first_value = float_values[0]
                second_value = float_values[1]

                # Extract execution time from the output (assuming it's in the format "Execution Time: <time>")
                writer.writerow([tasks, first_value, second_value])

            except subprocess.CalledProcessError as e:
                print(f"Error details: {e}")

print(f"Execution times have been saved to {output_file}.")