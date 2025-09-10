import matplotlib.pyplot as plt 
import scienceplots
import numpy as np
plt.style.use(['science', 'nature', 'grid', 'vibrant'])
# plt.style.use(['science', 'ieee', 'grid', 'vibrant'])


def get_xs_and_us(filename):
    with open(filename, "r") as file:

        xs = []; vs = []

        reading_contents = False
        for line in file:
            tmp = line.split(",")
            if tmp[0] == "x": # New batch of values
                reading_contents = True
                N = int(tmp[-1])
                xs.append(np.zeros(N)); vs.append(np.zeros(N))
                i = 0
                continue 

            if reading_contents:
                xs[-1][i] = float(tmp[0]); vs[-1][i] = float(tmp[1])
                i += 1

    return xs, vs


if __name__ == "__main__":
    filename = "problem2.txt"
    xs, us  = get_xs_and_us(filename)

    plt.plot(xs[2], us[2]) # n_steps = 98
    plt.xlabel("x")
    plt.ylabel("u")
    plt.savefig("../Figs/problem2.pdf")
    plt.show()