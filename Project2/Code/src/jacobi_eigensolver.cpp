#include "jacobi_eigensolver.hpp"

void jacobi_rotate(arma::mat &A, arma::mat &R, int k, int l)
{

    double a_kk = A(k, k);
    double a_ll = A(l, l);
    double a_kl = A(k, l);

    double t;
    double c;
    double s;

    double tau = (a_ll - a_kk) / (2 * a_kl);

    if (tau > 0)    // Smallest tau value will give faster convergence
    {
        t = 1.0 / (tau + std::sqrt(1 + tau * tau));
    }
    else
    {
        t = -1.0 / (-tau + std::sqrt(1 + tau * tau));
    }

    c = 1.0 / std::sqrt(1 + t * t);
    s = c * t;

    // Update A

    A(k, k) = a_kk * c * c - 2 * a_kl * c * s + a_ll * s * s;
    A(l, l) = a_ll * c * c + 2 * a_kl * c * s + a_kk * s * s;
    A(k, l) = 0;
    A(l, k) = 0;

    for (int i = 0; i < A.n_rows; i++)
    {
        if (i != k && i != l)
        {
            double a_ik = A(i, k);
            double a_il = A(i, l);

            A(i, k) = a_ik * c - a_il * s;
            A(k, i) = A(i, k);
            A(i, l) = a_il * c + a_ik * s;
            A(l, i) = A(i, l);
        }
    }

    // Update R

    for (int i = 0; i < R.n_rows; i++)
    {
        double r_ik = R(i, k);
        double r_il = R(i, l);

        R(i, k) = r_ik * c - r_il * s;
        R(i, l) = r_il * c + r_ik * s;
    }
}

void jacobi_eigensolver(
    const arma::mat &A, 
    double eps, 
    arma::vec 
    &eigenvalues, 
    arma::mat &eigenvectors, 
    const int maxiter, 
    int &iterations, 
    bool &converged)
{  
    iterations = 0;

    arma::mat A_m = A; // Copy of A to be changed
    arma::mat R_m = arma::eye(A.n_rows, A.n_rows);

    int k, l;
    double max_offdiag = max_offdiag_symmetric(A_m, k, l);
    
    while (std::abs(max_offdiag) > eps and iterations < maxiter)
    {
        jacobi_rotate(A_m, R_m, k, l);
        max_offdiag = max_offdiag_symmetric(A_m, k, l);

        iterations++;
    }

    eigenvalues = A_m.diag();
    eigenvectors = R_m;
    iterations = iterations;
    converged = (max_offdiag <= eps);
}