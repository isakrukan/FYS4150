#ifndef PROBLEMS
#define PROBLEMS
#include <string>

/**
 * @brief Iterates from \f$N=5\f$ to @p N_max, and for each iteration creating a symmetric \f$N\times N\f$ matrix
 * using @ref triDag::create_tridiaginal and computing the eigenvalues using Jacobi's rotation method implemented in 
 * @ref jacobi_eigensolver::jacobi_eigensolver. Writes the result to @p outfile.
 * 
 * @param N_max     Final size of matrix.
 * @param tol       Tolerance passed to @ref jacobi_eigensolver::jacobi_eigensolver.
 * @param maxiter   Maximum number of iterations.
 * @param outfile   File to write results to.
 */
void problem_5(double N_max, double tol, int maxiter, const std::string &outfile);


/**
 * @brief Creates a tridiagonal matrix using @ref triDag::create_tridiagonal, computes its eigenvalues and eigenvectors using Jacobi's
 * rotation method implemented in @ref jacobi_eigensolver::jacobi_eigensolver. Writes these eigenvalues and eigenvectors to @ref outfile
 * 
 * @param n_steps   Number if steps for Jacobi's rotation method (1 - size of tridiagonal matrix).
 * @param tol       Tolerance passed to @ref jacobi_eigensolver::jacobi_eigensolver.
 * @param maxiter   Maximum number of iterations.
 * @param outfile   File to write results to.
 */
void problem_6(int n_steps, double tol, int maxiter, const std::string &outfile);

#endif