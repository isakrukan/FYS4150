#include <armadillo>

/**
 * Creates a symmetric tridiagonal matrix of size n x n with constant
 * diagonal elements d, sub-diagonal elements a, and super-diagonal elements e.
 * @param n size of the matrix
 * @param a sub-diagonal elements
 * @param d diagonal elements
 * @param e super-diagonal elements
 * @return the tridiagonal matrix
 */
arma::mat create_tridiagonal(int n, double a, double d, double e);

double max_offdiag_symmetric(const arma::mat &A, int &k, int &l);