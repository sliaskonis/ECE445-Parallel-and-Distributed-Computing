import matplotlib.pyplot as plt
import numpy as np
import re
import subprocess
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib.backends.backend_pdf import PdfPages

# Number of threads to test
threads = [4]

# Initialize lists to store execution times for each chunk
chunk1_times = []
chunk2_times = []
chunk3_times = []
pattern = r"Thread=(\d+).*?i\s*=\s*(\d+)\s*,\s*j\s*=\s*(\d+).*?k\s*=\s*(\d+)"
chunk1_array = []
chunk2_array = []
chunk3_array = []

for thread_count in threads:
    chunk1_array = []
    chunk2_array = []
    chunk3_array = []
    #print(thread_count)
    ch=[2,3,4]
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

    # chunk1_time = float(re.search(r"Wall Clock Time = \s*([\d.]+)", output1).group(1))
    # chunk2_time = float(re.search(r"Wall Clock Time = \s*([\d.]+)", output2).group(1))
    # chunk3_time = float(re.search(r"Wall Clock Time = \s*([\d.]+)", output3).group(1))
    # print(chunk1_times)
    # print(chunk2_times)
    # print(chunk3_times)
    # print("\n")


    chunk1_temp_array = re.findall(pattern, output1)
    chunk2_temp_array = re.findall(pattern, output2)
    chunk3_temp_array = re.findall(pattern, output3)
    chunk1_array.extend(chunk1_temp_array)
    chunk2_array.extend(chunk2_temp_array)
    chunk3_array.extend(chunk3_temp_array)
    ########### EXCEL STAFF #################
    excel_data=[]
    arrays = [chunk1_array, chunk2_array, chunk3_array]
    #print(arrays)
    thread_distr_array=[]
    for j, chunks in enumerate(arrays):
        chunks = [(int(thread), int(i), int(j), int(k)) for thread, i, j, k in chunks]
        chunks = list(set(chunks))  # Remove duplicates
        chunks = sorted(chunks, key=lambda x: (x[1], x[2], x[3]))  # Sort and reassign to chunk3_array
        
        result = {}
        for thread, i, j, k in chunks:
            if (i, j) not in result:
                result[(i, j)] = []
            result[(i, j)].append((thread, i, j, k))
        max_i = max(key[0] for key in result.keys())
        max_j = max(key[1] for key in result.keys())
        # Create a 2D array
        array_2d = [[result.get((i, j), []) for j in range(max_j + 1)] for i in range(max_i + 1)]
        
        thread_distr_array.append(array_2d)
        print(array_2d)

    for c,chunk in enumerate(thread_distr_array):
        for i,row in enumerate(chunk):
            for j,col in enumerate(row): 
                string = ""
                print("---->",thread_distr_array[c][i][j])
                for t in col:
                    string += f"{str(t[0])}"
                thread_distr_array[c][i][j]=string
                print("<----",thread_distr_array[c][i][j])

    # Export to PDF
    for c, chunk in enumerate(thread_distr_array):
        pdf_output = f"DLevel3_chunk{ch[c]}.pdf"
        with PdfPages(pdf_output) as pdf:
            max_i = len(chunk)
            max_j = len(chunk[0])
            
            # Create a DataFrame similar to Excel for easy display
            df = pd.DataFrame(index=[f"i={i}" for i in range(max_i)], columns=[f"j={j}" for j in range(max_j)])
            for i, row in enumerate(chunk):
                for j, col in enumerate(row):
                    df.iloc[i, j] = col
            
            # Add the title row and labels
            full_df = pd.DataFrame(columns=[""] + list(df.columns))
            full_df.loc["", ""] = "thread_id for all k(for each i,j)"
            for col in df.columns:
                full_df.loc["", col] = col
            for i, index_label in enumerate(df.index):
                full_df.loc[index_label] = [index_label] + list(df.iloc[i])
            
            # Plotting the table
            fig, ax = plt.subplots(figsize=(4, 2))  # Adjust the size as needed
            ax.axis('tight')
            ax.axis('off')
            table = ax.table(cellText=full_df.values, colLabels=None, loc='center', cellLoc='center')
            table.auto_set_font_size(False)
            table.set_fontsize(10)
            table.auto_set_column_width(col=list(range(len(full_df.columns))))  # Auto-adjust column widths
            
            # Add to PDF
            pdf.savefig(fig)
            plt.close(fig)
        print()
        print(f"Data exported to PDF: {pdf_output}")