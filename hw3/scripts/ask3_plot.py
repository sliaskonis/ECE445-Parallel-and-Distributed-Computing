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
first_half_sizes = unique_sizes[:6]
second_half_sizes = unique_sizes[6:]

# Function to plot data with a single legend entry for the red dot
def plot_subset(subset_sizes, title):
    plt.figure(figsize=(10, 6))
    min_marker_added = False  # Flag to ensure only one legend entry for the red dot

    for size in subset_sizes:
        subset = average_times[average_times['Array_Size'] == size]
        x = subset['Num_Processors'].to_numpy()
        y = subset['Execution_Time'].to_numpy()
        plt.plot(x, y, label=f"Size {size}")

        # Find the lowest execution time and its corresponding Num_Processors
        min_idx = y.argmin()
        if not min_marker_added:
            plt.scatter(x[min_idx], y[min_idx], color='red', marker='o', s=100, edgecolor='black', label="Min Value")
            min_marker_added = True  # Ensure the legend entry is added only once
        else:
            plt.scatter(x[min_idx], y[min_idx], color='red', marker='o', s=100, edgecolor='black')

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