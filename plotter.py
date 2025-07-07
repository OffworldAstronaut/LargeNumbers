import numpy as np
import matplotlib.pyplot as plt
import os, glob

avg_array = []

file_name = glob.glob(os.path.join(os.getcwd(), "*.dat"), recursive=True)

with open(file_name[0], 'r') as f:
    data = f.readlines()
    data = [float(line) for line in data if line.strip().isdigit()]
    expected_value = data[-1]
    data.pop()

for i in range(len(data)):
    avg = np.mean(data[0:i+1])
    avg_array.append(avg)
    
plt.plot(avg_array, label='Average Value')
plt.axhline(y=expected_value, color='r', linestyle='--', label='Expected Value')
plt.xlabel('Number of Samples')
plt.ylabel('Average Value')
plt.title('Average Value Convergence')
plt.legend()
plt.grid()
plt.savefig('average_convergence.png')