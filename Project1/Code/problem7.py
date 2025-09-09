import matplotlib.pyplot as plt 
import scienceplots
import numpy as np
from problem2 import get_x_and_u

plt.style.use(['science', 'nature', 'grid', 'vibrant'])
# plt.style.use(['science', 'ieee', 'grid', 'vibrant'])

filename = "problem7.txt"

with open(filename, "r") as file:

    xs = []; vs = []

    reading_contents = False
    for line in file:
        tmp = line.split(",")
        if tmp[0] == "x": # New batch of values
            reading_contents = True
            N = int(tmp[-1])
            print(N)
            xs.append(np.zeros(N)); vs.append(np.zeros(N))
            i = 0
            continue 

        if reading_contents:
            xs[-1][i] = float(tmp[0]); vs[-1][i] = float(tmp[1])
            i += 1

x, u = get_x_and_u("problem2.txt")


def u_func(x):
    return 1 - (1 - np.exp(-10))*x - np.exp(-10*x)

plt.plot(xs[0], vs[0], label=f"numerical (n={len(xs[0])-2})")
plt.plot(xs[1], vs[1], label=f"numerical (n={len(xs[1])-2})")
plt.plot(x, u, label="analytic") # analytic
plt.legend()
plt.xlabel("x")
plt.savefig("../Figs/problem7.pdf")
plt.show()