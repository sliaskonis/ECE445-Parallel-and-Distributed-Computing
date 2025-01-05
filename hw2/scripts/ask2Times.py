import matplotlib.pyplot as plt
import numpy as np
import re
import subprocess
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

# Number of threads to test
threads = [2, 3, 4, 5, 6, 7, 8]
'''1, 2, 3, 4, 5, 6, 7, 8'''

# Initialize lists to store execution times for each chunk
chunk1_times = []
chunk2_times = []
chunk3_times = []
pattern = r"Thread=(\d+).*?i\s*=\s*(\d+)\s*,\s*j\s*=\s*(\d+).*?k\s*=\s*(\d+)"

for thread_count in threads:
    ch=[10,20,40]
    result1 = subprocess.run(
        ["./bin/ask2_p_A", str(thread_count), str(ch[0])],
        capture_output=True,
        text=True
    )
    result2 = subprocess.run(
        ["./bin/ask2_p_A", str(thread_count), str(ch[1])],
        capture_output=True,
        text=True
    )
    result3 = subprocess.run(
        ["./bin/ask2_p_A", str(thread_count), str(ch[2])],
        capture_output=True,
        text=True
    )
    output1 = result1.stdout.strip()
    output2 = result2.stdout.strip()
    output3 = result3.stdout.strip() #"Total Parallel Time = %.6f sec.\n"

    chunk1_time = float(re.search(r"Wall Clock Time = \s*([\d.]+)", output1).group(1))
    chunk2_time = float(re.search(r"Wall Clock Time = \s*([\d.]+)", output2).group(1))
    chunk3_time = float(re.search(r"Wall Clock Time = \s*([\d.]+)", output3).group(1))
    chunk1_times.append(chunk1_time)
    chunk2_times.append(chunk2_time)
    chunk3_times.append(chunk3_time)
    print(chunk1_times)
    print(chunk2_times)
    print(chunk3_times)
    print("\n")

########################## TIMES PLOT #######################################

# Data
execution_times = [chunk1_times, chunk2_times, chunk3_times]
chunk_labels = ['Chunk = 10', 'Chunk = 20', 'Chunk = 40']
x = np.arange(len(threads))  # X positions for each thread count
width = 0.25  # Width of each bar

# Plot
fig, ax = plt.subplots(figsize=(10, 6))
for i, times in enumerate(execution_times):
    ax.bar(x + i * width, times, width, label=chunk_labels[i])

# Labels and title
ax.set_xlabel('Number of Threads')
ax.set_ylabel('Execution Time')
ax.set_title('Execution Time vs Number of Threads')
ax.set_xticks(x + width)
ax.set_xticklabels(threads)
ax.legend()

# Display grid and plot
plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()

# Save the plot
plot_filename = "DLEVEL3_execution_time_vs_threads.png"  # Change to .pdf, .jpg, etc., if needed
plt.savefig(plot_filename, dpi=300, format='png')  # Set DPI for higher quality
print(f"Plot saved as: {plot_filename}")

# Show the plot (optional, can be commented if not needed)
plt.show()
