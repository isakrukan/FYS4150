import matplotlib.pyplot as plt 
import scienceplots
import numpy as np
plt.style.use(['science', 'nature', 'grid', 'vibrant'])
# plt.style.use(['science', 'ieee', 'grid', 'vibrant'])

filename = "problem2.txt"

with open(filename, "r") as file:
    header = file.readline()
    N = int(header.split(",")[-1])

    x = np.zeros(N)
    u = np.zeros(N)

    i = 0
    for line in file:
        tmp = line.split(",")
        x[i] = float(tmp[0]); u[i] = float(tmp[1])
        i += 1



plt.plot(x, u)
plt.xlabel("x")
plt.savefig("../Figs/problem2.pdf")
plt.show()