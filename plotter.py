# Library imports
import numpy as np                  # Numerical operations
import matplotlib.pyplot as plt     # Plotting
import os, glob                     # File handling

# Array to store the average values for plotting
avg_array = []

# Finds the .dat file produced by the C++ program
file_name = glob.glob(os.path.join(os.getcwd(), "*.dat"))

# Reads the file, converts the strings to floats and extracts the expected value
with open(file_name[0], 'r') as f:
    data = f.readlines()
    data = [float(line) for line in data]
    expected_value = data[-1]  # The last line is the expected value
    data.pop()  # Remove the last line from the data

# Calculates the average values for incresingly larger sample sizes, storing them in avg_array
for i in range(len(data)):
    avg = np.mean(data[0:i+1])
    avg_array.append(avg)
    
# Plots the average values and the expected value
plt.plot(avg_array, label='Average Value')
plt.axhline(y=expected_value, color='r', linestyle='--', label='Expected Value')
plt.xlabel('Number of Samples')
plt.ylabel('Average Value')
plt.title('Average Value Convergence')
plt.legend()
plt.grid()
plt.savefig('average_convergence.png')