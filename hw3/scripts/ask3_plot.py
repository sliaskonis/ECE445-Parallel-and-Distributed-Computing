import pandas as pd
import matplotlib.pyplot as plt
import sys

if len(sys.argv) != 2:
    print("Usage: python ask3_plot.py <csv_file>")
    exit(1)

# Load the CSV file into a DataFrame
df = pd.read_csv(sys.argv[1])

# Convert the execution time to float
df['Execution_Time'] = pd.to_numeric(df['Execution_Time'], errors='coerce')

# Group by Array_Size and Num_Processors, then calculate the mean execution time
average_times = df.groupby(['Array_Size', 'Num_Processors'])['Execution_Time'].mean().reset_index()

# Get the unique array sizes and determine the midpoint
unique_sizes = sorted(average_times['Array_Size'].unique())
midpoint = len(unique_sizes) // 2

# Split array sizes into two groups
first_half_sizes = unique_sizes[:midpoint]
second_half_sizes = unique_sizes[midpoint:]

# Function to plot data
def plot_subset(subset_sizes, title):
    plt.figure(figsize=(10, 6))
    for size in subset_sizes:
        subset = average_times[average_times['Array_Size'] == size]
        x = subset['Num_Processors'].to_numpy()
        y = subset['Execution_Time'].to_numpy()
        plt.plot(x, y, label=f"Size {size}")
    plt.xlabel("Number of Processors")
    plt.ylabel("Average Execution Time (seconds)")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.show()

# Plot first half
plot_subset(first_half_sizes, "Average Execution Time for Array Sizes (First Half)")

# Plot second half
plot_subset(second_half_sizes, "Average Execution Time for Array Sizes (Second Half)")