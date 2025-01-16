import re
from fpdf import FPDF

# Sample terminal output (replace with your actual captured output)
terminal_output = """
Hello. This is node 2.
Hello. This is node 3.
Hello. This is node 1.
Processor: ostralis-Lenovo-ideapad-330S-15IKB, Number of tasks = 4
Hello. This is the master node.
Average time for (datatype: int) = 0.000002 seconds
Average time for (datatype: float) = 0.000002 seconds
Average time for (datatype: double) = 0.000001 seconds
"""

# Extract data from the terminal output
number_of_tasks = re.search(r"Number of tasks = (\d+)", terminal_output).group(1)
average_times = re.findall(r"Average time for \(datatype: (\w+)\) = ([\d\.]+) seconds", terminal_output)

# Create the data array
data = [
    ["Number of Tasks = 4", "int", "float", "double"],  # Header row
    ["Time (sec)", average_times[0][1], average_times[1][1], average_times[2][1]]  # Data row
]

# Generate the PDF
class PDF(FPDF):
    def header(self):
        self.set_font("Arial", "B", 12)
        # self.cell(0, 10, "Average Times Report", 0, 1, "C")
        self.ln(10)

    def table(self, data):
        self.set_font("Arial", size=10)
        col_widths = [50, 40, 40, 40]  # Column widths
        for row in data:
            for i, item in enumerate(row):
                self.cell(col_widths[i], 10, str(item), border=1, align="C")
            self.ln()

# Create PDF instance and add data
pdf = PDF(format=(200, 65))
pdf.add_page()
pdf.table(data)

# Save the PDF
pdf.output("average_times.pdf")
print("PDF generated: average_times.pdf")
