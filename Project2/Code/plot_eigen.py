import numpy as np
import matplotlib.pyplot as plt
plt.style.use('ggplot')

import pandas as pd


fig, ax = plt.subplots(nrows=2, sharex=True, figsize=(8, 6))

for i, n_steps in enumerate([10, 100]):
    data = pd.read_csv(f'output/eigen-n{n_steps}.csv', sep=r'\s+', header=None).to_numpy()
    eig_vals = data[0, :]
    eig_vecs = data[2:, :]

    N = eig_vecs.shape[0]

    h = 1 / (N + 1)
    x_0 = h
    x_N = 1 - h
    x = np.linspace(x_0, x_N, N)

    indices = np.argsort(eig_vals)

    for n in range(3):
        ax[i].plot(x, eig_vecs[:, indices[n]], label=f'$\lambda_{n}$')

    ax[i].set_title(r'$n_\mathrm{steps}' + f' = {n_steps}$')
plt.legend()
plt.savefig('output/eigenvectors.pdf')