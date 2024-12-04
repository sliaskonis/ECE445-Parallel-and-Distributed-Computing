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
                    # Calculate mean and std across iterations for each K value
                    iteration_array = np.array(iteration_times)
                    data[current_size] = {
                        'mean': np.mean(iteration_array, axis=0),
                        'std': np.std(iteration_array, axis=0)
                    }
                
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
            iteration_array = np.array(iteration_times)
            data[current_size] = {
                'mean': np.mean(iteration_array, axis=0),
                'std': np.std(iteration_array, axis=0)
            }
    
    return data

def plot_data(data):
    k_values = [1, 2, 4, 8, 16]
    
    for array_size, stats in data.items():
        mean_times = stats['mean']
        std_times = stats['std']
        
        if len(mean_times) != 5 or len(std_times) != 5:
            print(f"Warning: Array size {array_size} does not have exactly 5 mean times.")
            continue
        
        plt.figure(figsize=(10, 6))
        
        # Plotting mean execution times with error bars for standard deviation
        bars = plt.bar(k_values, mean_times, yerr=std_times, capsize=5, color='#008AC5', error_kw={'ecolor': 'black'})
        
        # Set axis labels with darker grey color
        plt.xlabel("K (Loop Unroll Factor)", color="#7D7D7D")
        plt.ylabel("Mean Execution Time (seconds)", color="#7D7D7D")
        plt.title(f"Mean Execution Time with Standard Deviation for Array Size = {array_size}")
        plt.xticks(k_values)
        
        # Move gridlines behind bars and display only horizontal grid lines
        plt.gca().set_axisbelow(True)
        plt.grid(axis='y', linestyle='--', alpha=0.7)
        
        # Remove ticks
        plt.tick_params(axis='both', which='both', length=0)
        
        # Adding mean values on top of the bars in the same color as the bars with 5 decimal precision
        for bar, mean_time in zip(bars, mean_times):
            yval = bar.get_height()
            plt.text(bar.get_x() + bar.get_width() / 2, yval + std_times.mean() * 0.1, 
                     f"{mean_time:.5f}", ha='center', va='bottom', color='#008AC5', fontsize=10)

        plt.show()

def main():
    parser = argparse.ArgumentParser(description="Plot execution times from a results file.")
    parser.add_argument("filename", type=str, help="Path to the results file")
    args = parser.parse_args()
    
    data = read_data(args.filename)
    plot_data(data)

if __name__ == "__main__":
    main()