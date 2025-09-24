from scipy.stats import linregress
import numpy as np
import matplotlib.pyplot as plt
from utils import latex_fonts

latex_fonts(double_coulmn=True)
plt.style.use('ggplot')

# Loading data:
data = np.loadtxt('output/problem5.csv', delimiter=',')

# Extracting data:
N = data[:, 0]
iterations = data[:, 1]

# Log of data:
logN = np.log(N)
logIter = np.log(iterations)

# Linear regression of log(data):
slope, intercept, r_value, p_value, std_err = linregress(logN[:-1], logIter[:-1])
iter_fit = np.exp(intercept) * N**slope
print(f"Slope: {slope}, Intercept: {intercept}, R-squared: {r_value**2}")

# Plots the data:
plt.plot(N, iterations, "k", marker='o', label='Data Points')
plt.plot(N, iter_fit, "--r", label=rf'$y = {np.exp(intercept):.2f}\ N^' + r'{' + f'{slope:.2f}' + r'}$')
plt.xlim(0, max(N))
plt.ylim(0, max(iterations))
plt.ticklabel_format(style='sci', axis='y', scilimits=(0,0))
# plt.ticklabel_format(style='sci', axis='x', scilimits=(0,0))

plt.xlabel('Matrix Size N')
plt.ylabel('Number of transformations')
plt.legend()
plt.savefig('output/iterations.pdf')
