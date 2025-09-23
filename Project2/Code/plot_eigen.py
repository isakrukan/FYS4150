import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
plt.style.use('ggplot')


# Analytical solutions

x_anal = np.linspace(0, 1, 1000)
sol_anal = np.zeros((1000, 3))
sol_anal[:, 0] = np.sin(np.pi * x_anal)
sol_anal[:, 1] = np.sin(2 * np.pi * x_anal)
sol_anal[:, 2] = np.sin(3 * np.pi * x_anal)

colors = ['C0', 'C1', 'C2']

fig, ax = plt.subplots(nrows=2, sharex=True, figsize=(8, 6))

for i, n_steps in enumerate([10, 100]):
    data = pd.read_csv(f'output/eigen-n{n_steps}.csv', sep=r'\s+', header=None).to_numpy()
    eig_vals = data[0, :]
    eig_vecs = data[1:, :]
    
    N = eig_vecs.shape[0]

    sol_num = np.zeros((N+2, eig_vecs.shape[1]))
    sol_num[1:-1, :] = eig_vecs
    x_num = np.linspace(0, 1, N+2)

    sol_num /= np.max(sol_num)

    # Find indices to sort by eigenvalue
    idx = np.argsort(eig_vals)


    # Manually flip some eigenvectors for clearer comparison
    if n_steps == 10:
        sol_num[:, idx[2]] *= -1

    if n_steps == 100:
        sol_num[:, idx[1]] *= -1
    
    for n in range(3):
        ax[i].plot(x_num, sol_num[:, idx[n]], color=colors[n], alpha=0.6, label=f'$\lambda_{n}$')
        ax[i].plot(x_anal, sol_anal[:, n], color=colors[n], linestyle=":", label=f'Analytic $\lambda_{n}$')

    ax[i].set_title(r'$n_\mathrm{steps}' + f' = {n_steps}$')
    ax[i].set_ylabel('v(x)')
    
from matplotlib.lines import Line2D
from matplotlib.legend_handler import HandlerTuple
legend_elements = []
for i in range(3):
    num_line = Line2D([0], [0], color=colors[i], linestyle=':')
    ana_line = Line2D([0], [0], color=colors[i], linestyle='-')
    legend_elements.append((num_line, ana_line))

plt.legend(legend_elements, [r'$v^{(' + f'{i}' + ')}$' for i in range(3)],
           handler_map={tuple: HandlerTuple(ndivide=None)},
           ncol=1)
plt.xlabel('x/L')
#plt.legend()
plt.savefig('output/eigenvectors.pdf')