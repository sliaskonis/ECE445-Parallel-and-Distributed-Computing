import matplotlib.pyplot as plt
import numpy as np
import argparse
from matplotlib.patches import Rectangle

def read_data(filename):
    data = {}
    with open(filename, 'r') as file:
        current_size = None
        iteration_times = []
        current_iteration = []

        for line in file:
            line = line.strip()
            if line.startswith("ArraySize="):
                # Save previous data if exists
                if current_size and iteration_times:
                    # Calculate the mean across iterations for each K value
                    data[current_size] = np.mean(iteration_times, axis=0)
                
                # Start a new array size section
                current_size = int(line.split('=')[1])
                iteration_times = []
            
            elif line.startswith("Iteration"):
                # If we have times from the previous iteration, add it to iteration_times
                if current_iteration:
                    iteration_times.append(current_iteration)
                # Start a new iteration
                current_iteration = []
            
            else:
                # Append the execution time for the current iteration
                try:
                    time = float(line)
                    current_iteration.append(time)
                except ValueError:
                    print(f"Skipping invalid line: {line}")
        
        # Save the last iteration and array size section
        if current_iteration:
            iteration_times.append(current_iteration)
        if current_size and iteration_times:
            data[current_size] = np.mean(iteration_times, axis=0)
    
    return data

def plot_data(data):
    k_values = [1, 2, 4, 8, 16]
    
    for array_size, mean_times in data.items():
        if len(mean_times) != 5:
            print(f"Warning: Array size {array_size} does not have exactly 5 mean times.")
            continue
        
        plt.figure(figsize=(8, 5))
        plt.plot(k_values, mean_times, marker='o')
        
        # Set axis labels with grey color
        plt.xlabel("K (Loop Unroll Factor)", color="#7D7D7D")
        plt.ylabel("Mean Execution Time (seconds)", color="#7D7D7D")
        plt.title(f"Mean Execution Time for Array Size = {array_size}")
        
        # Ensure the default axis box is visible
        plt.gca().spines['top'].set_visible(True)
        plt.gca().spines['right'].set_visible(True)
        plt.gca().spines['left'].set_visible(True)
        plt.gca().spines['bottom'].set_visible(True)
        
        # You can adjust the width and color of the axis box if needed
        plt.gca().spines['top'].set_linewidth(1)
        plt.gca().spines['right'].set_linewidth(1)
        plt.gca().spines['left'].set_linewidth(1)
        plt.gca().spines['bottom'].set_linewidth(1)
        plt.gca().spines['top'].set_color('black')
        plt.gca().spines['right'].set_color('black')
        plt.gca().spines['left'].set_color('black')
        plt.gca().spines['bottom'].set_color('black')
        
        # Remove gridlines
        plt.grid(False)
        
        plt.show()

def main():
    parser = argparse.ArgumentParser(description="Plot execution times from a results file.")
    parser.add_argument("filename", type=str, help="Path to the results file")
    args = parser.parse_args()
    
    data = read_data(args.filename)
    plot_data(data)

if __name__ == "__main__":
    main()