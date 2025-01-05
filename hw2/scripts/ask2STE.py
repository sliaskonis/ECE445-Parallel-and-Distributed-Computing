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

result = subprocess.run(
    ["./bin/ask2_s"],
    capture_output=True,
    text=True
)
output = result.stdout.strip()
Ts = float(re.search(r"Total Parallel Time = \s*([\d.]+)", output).group(1))
ch=[10,20,40]
for thread_count in threads:
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


# Export to PDF
# for c, chunk in enumerate(execution_times):
pdf_output = f"L1stats.pdf"
with PdfPages(pdf_output) as pdf:
    max_j = len(ch)
    max_i = len(execution_times[0])
    print("Ts=",Ts)
    # Create a DataFrame similar to Excel for easy display
    df = pd.DataFrame(index=[f"{i}" for i in range(max_i)], columns=[f"{j}" for j in range(max_j)])
    for i, row in enumerate(ch):
        for j, col in enumerate(execution_times[i]):
            Sp = f"{Ts/col:.6f}"
            Ep = f"{Ts/(col*threads[i]):.6f}"
            print(str(col)+", " +str(Sp)+", " +str(Ep),"----", str(threads[i]))
            df.iloc[j,i] = str(col)+", " +str(Sp)+", " +str(Ep)
    
    # Add the title row and labels
    full_df = pd.DataFrame(columns=[""] + list(df.columns))
    full_df.loc["", ""] = "Nthreads \ chunk"
    for k,col in enumerate(df.columns):
        full_df.loc["", col] = str(ch[k])
    for i, index_label in enumerate(df.index):
        full_df.loc[index_label] = [str(threads[i])] + list(df.iloc[i])
    # Plotting the table
    fig, ax = plt.subplots(figsize=(12, 2))  # Adjust the size as needed
    ax.axis('tight')
    ax.axis('off')
    table = ax.table(cellText=full_df.values, colLabels=None, loc='center', cellLoc='center')
    table.auto_set_font_size(False)
    table.set_fontsize(10)
    table.auto_set_column_width(col=list(range(len(full_df.columns))))  # Auto-adjust column widths
    
    # Add to PDF
    pdf.savefig(fig)
    plt.close(fig)
print(f"Data exported to PDF: {pdf_output}")
