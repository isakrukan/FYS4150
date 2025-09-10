import matplotlib.pyplot as plt 
import numpy as np
from problem2 import get_xs_and_us

plt.style.use(['science', 'nature', 'grid', 'vibrant'])
# plt.style.use(['science', 'ieee', 'grid', 'vibrant'])


if __name__ == "__main__":
    filename = "problem7.txt"
    xs, vs = get_xs_and_us(filename)
    xs_, us = get_xs_and_us("problem2.txt")

    plt.plot(xs[0], vs[0], label=r"numerical ($n_{\text{steps}}$" + f"={len(xs[0])-2})", color="green")
    plt.plot(xs[1], vs[1], label=r"numerical ($n_{\text{steps}}$" + f"={len(xs[1])-2})", color="red")
    plt.plot(xs[-1], us[-1], label="analytic", color="blue") # analytic
    plt.legend()
    plt.xlabel("x")
    plt.savefig("../Figs/problem7.pdf")
    plt.show()