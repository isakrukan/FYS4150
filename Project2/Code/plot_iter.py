from scipy.stats import linregress
import numpy as np
import matplotlib.pyplot as plt
plt.style.use('ggplot')

data = np.loadtxt('output/problem5.csv', delimiter=',')

N = data[:, 0]
iterations = data[:, 1]


logN = np.log(N)
logIter = np.log(iterations)

slope, intercept, r_value, p_value, std_err = linregress(logN[:-1], logIter[:-1])

print(f"Slope: {slope}, Intercept: {intercept}, R-squared: {r_value**2}")


iter_fit = np.exp(intercept) * N**slope

plt.figure(figsize=(8, 6))
plt.plot(N, iterations, "k", marker='o', label='Data Points')
plt.plot(N, iter_fit, "--r", label=f'$y = {np.exp(intercept):.2f}\ N^' + r'{' + f'{slope:.2f}' + r'}$')
plt.xlim(0, max(N))
plt.ylim(0, max(iterations))

plt.xlabel('Matrix Size N')
plt.ylabel('Number of transformations')
plt.legend()
plt.savefig('output/iterations.pdf')
