import matplotlib.pyplot as plt 
import numpy as np
from problem2 import get_xs_and_us


if __name__ == "__main__":
    filename = "problem7.txt"
    xs, vs = get_xs_and_us(filename)
    xs_, us = get_xs_and_us("problem2.txt")

    abs_error = []
    rel_error = []
    for i in range(len(xs)): # Iterating over n_steps
        tmp = np.log10(np.abs(us[i][1:-1] - vs[i][1:-1]))   # skipping first and last element (since zero)
        abs_error.append(tmp)

        tmp = np.log10(np.abs((us[i][1:-1] - vs[i][1:-1])/us[i][1:-1])) # skipping first and last element (since zero)
        rel_error.append(tmp)

include_these = [0, 1, 2]
colors = ["green", "red", "blue"]
for i in include_these:
    plt.plot(xs[i][1:-1], abs_error[i], label=r"n_{\text{steps}} = " + str(len(xs[i])-2), color=colors[i])

plt.title("Absolute Error")
plt.xlabel("x")
plt.ylabel(r"$log_{10}(|u - v|)$")
plt.legend()
plt.savefig("../Figs/problem8_abs_error.pdf")
plt.show()

for i in include_these:
    plt.plot(xs[i][1:-1], rel_error[i], label=r"n_{\text{steps}} = " + str(len(xs[i])-2), color=colors[i])

plt.title("Relative Error")
plt.xlabel("x")
plt.ylabel(r"$log_{10}(|(u - v)/u|)$")
plt.legend()
plt.savefig("../Figs/problem8_rel_error.pdf")
plt.show()

# plt.plot(xs[1], vs[1])
# plt.plot(xs[1], us[1])
# plt.show()
