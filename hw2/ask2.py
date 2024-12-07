import matplotlib.pyplot as plt
import numpy as np
import re
import subprocess
import pandas as pd

# Number of threads to test
threads = [1, 2, 3, 4, 5, 6, 7, 8]
'''1, 2, 3, 4, 5, 6, 7, 8'''

# Initialize lists to store execution times for each chunk
chunk1_times = []
chunk2_times = []
chunk3_times = []
pattern = r"Thread=(\d+).*?i\s*=\s*(\d+)\s*,\s*j\s*=\s*(\d+)"
chunk1_array = []
chunk2_array = []
chunk3_array = []

for thread_count in threads:
    print(thread_count)
    result1 = subprocess.run(
        ["./ask2_p_A", str(thread_count), str(10)],
        capture_output=True,
        text=True
    )
    result2 = subprocess.run(
        ["./ask2_p_A", str(thread_count), str(20)],
        capture_output=True,
        text=True
    )
    result3 = subprocess.run(
        ["./ask2_p_A", str(thread_count), str(40)],
        capture_output=True,
        text=True
    )
    output1 = result1.stdout.strip()
    output2 = result2.stdout.strip()
    output3 = result3.stdout.strip() #"Total Parallel Time = %.6f sec.\n"

    chunk1_time = float(re.search(r"Total Parallel Time =\s*([\d.]+)", output1).group(1))
    chunk2_time = float(re.search(r"Total Parallel Time =\s*([\d.]+)", output2).group(1))
    chunk3_time = float(re.search(r"Total Parallel Time =\s*([\d.]+)", output3).group(1))
    chunk1_times.append(chunk1_time)
    chunk2_times.append(chunk2_time)
    chunk3_times.append(chunk3_time)
    print(chunk1_times)
    print(chunk2_times)
    print(chunk3_times)
    print("\n")


    chunk1_temp_array = re.findall(pattern, output1)
    chunk2_temp_array = re.findall(pattern, output2)
    chunk3_temp_array = re.findall(pattern, output3)
    chunk1_array.append(chunk1_temp_array)
    chunk2_array.append(chunk2_temp_array)
    chunk3_array.append(chunk3_temp_array)

arrays = [chunk1_array, chunk2_array, chunk3_array]
print(arrays)
'''
for i, array in enumerate(arrays):
    for j, chunks in enumerate(array):
        chunks = [(int(thread), int(i), int(j)) for thread, i, j in chunks]
        chunks = list(set(chunks))  # Remove duplicates
        chunks = sorted(chunks, key=lambda x: (x[0], x[1], x[2]))  # Sort and reassign to chunk3_array
        print(chunks)  # Now it will be sorted
        print("\n")
        df = pd.DataFrame(chunks, columns=['Thread', 'i', 'j'])
        df.to_excel(f"thread{i}_chunk{j%3}.xlsx", index=False)
'''
excel_data=[]
for i, array in enumerate(arrays):
    ch=[]
    for j, chunks in enumerate(array):
        chunks = [(int(thread), int(i), int(j)) for thread, i, j in chunks]
        chunks = list(set(chunks))  # Remove duplicates
        chunks = sorted(chunks, key=lambda x: (x[0], x[1], x[2]))  # Sort and reassign to chunk3_array
        #print(chunks)  # Now it will be sorted
        #print("\n")
        df = pd.DataFrame(chunks, columns=['Thread', 'i', 'j'])
        df.to_excel(f"thread{i}_chunk{j%3}.xlsx", index=False)
        ch.append(chunks)
    df_chunk1 = pd.DataFrame(ch[0], columns=['Thread 1', 'i 1', 'j 1'])
    df_chunk2 = pd.DataFrame(ch[1], columns=['Thread 2', 'i 2', 'j 2'])
    df_chunk3 = pd.DataFrame(ch[2], columns=['Thread 3', 'i 3', 'j 3'])

    # Concatenate the 3 chunks horizontally
    df_final = pd.concat([df_chunk1, df_chunk2, df_chunk3], axis=1)
    excel_data.append(df_final)

with pd.ExcelWriter('final_output.xlsx') as writer:
    for idx, df in enumerate(excel_data):
        df.to_excel(writer, sheet_name=f"Sheet_{idx+1}", index=False)



execution_times = [chunk1_times, chunk2_times, chunk3_times]
execution_times = [chunk1_times, chunk2_times, chunk3_times]
chunk_labels = ['Chunk1', 'Chunk2', 'Chunk3']

# Plotting
x = np.arange(len(threads))  # X positions for each thread count
width = 0.25  # Width of each bar

fig, ax = plt.subplots(figsize=(10, 6))

# Plot each chunk's data as a separate bar series
for i, times in enumerate(execution_times):
    ax.bar(x + i * width, times, width, label=chunk_labels[i])

# Labels and title
ax.set_xlabel('Number of Threads')
ax.set_ylabel('Execution Time (s)')
ax.set_title('Execution Time vs Number of Threads')
ax.set_xticks(x + width)
ax.set_xticklabels(threads)
ax.legend()
# Display grid and plot
plt.grid(True, linestyle='--', alpha=0.7)
plt.tight_layout()
plt.show()
plt.savefig("plot.pdf")
