import numpy as np
import matplotlib.pyplot as plt


def latex_fonts(double_coulmn=False):
    """
    Sets a bunch of parameters in matplotlib.pyplot to create nice figures.
    """
    # \the\columnwidth\par -> 246.0pt
    # \the\textwidth\par   -> 510.pt

    # Default fig_width, for UiO master thesis template type 
    fig_width_pt = 418.25368  # Get this from LaTeX using \showthe\columnwidth

    if double_coulmn:   # Double column report
        fig_width_pt = 246 + 25
    
    inches_per_pt = 1.0/72.27               # Convert pt to inch
    golden_mean = (np.sqrt(5)-1.0)/2.0         # Aesthetic ratio
    fig_width = fig_width_pt * inches_per_pt  # width in inches
    fig_height = fig_width * golden_mean      # height in inches
    fig_size =  [fig_width,fig_height]

    plt.rcParams['text.latex.preamble'] = r'\usepackage{mathrsfs}'
    
    plt.rcParams['text.usetex'] = True
    plt.rcParams['axes.titlepad'] = 10 
    plt.rcParams.update({
        'font.family': 'euclid',
        'font.weight': 'bold',
        'font.size': 10,       
        'axes.labelsize': 10,  
        'axes.titlesize': 10,  
        'xtick.labelsize': 10, 
        'ytick.labelsize': 10,
        'ytick.left': True,
        'xtick.bottom': True,
        'ytick.right': True,
        'xtick.top': True,
        'legend.fontsize': 10, 
        'figure.titlesize': 10,
        'legend.fontsize': 10,
        'figure.figsize': fig_size,
        'figure.subplot.bottom': 0.2,
    })
    # Ticks inside
    plt.rcParams['xtick.direction'] = 'in'
    plt.rcParams['ytick.direction'] = 'in'
    plt.rcParams['xtick.major.size'] = 4  # adjust tick length if you want
    plt.rcParams['ytick.major.size'] = 4
    plt.rcParams['xtick.minor.size'] = 2
    plt.rcParams['ytick.minor.size'] = 2