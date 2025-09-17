#ifndef JACOBI_EIGENSOLVER_HPP
#define JACOBI_EIGENSOLVER_HPP

#include <armadillo>
#include "utils.hpp"

/**
 * Performs a single Jacobi rotation.
 *
 * @param A The symmetric matrix to be diagonalized.
 * @param R The matrix of eigenvectors.
 * @param k The row index of the maximal off-diagonal element.
 * @param l The column index of the maximal off-diagonal element.
 */
void jacobi_rotate(arma::mat &A, arma::mat &R, int k, int l);

/**
 * Computes the eigenvalues and eigenvectors of a symmetric matrix using the Jacobi method.
 *
 * @param A The symmetric matrix to be diagonalized.
 * @param eps The convergence tolerance for the off-diagonal elements.
 * @param eigenvalues Vector to store the computed eigenvalues (output).
 * @param eigenvectors Matrix to store the computed eigenvectors (output).
 * @param maxiter The maximum number of iterations allowed.
 * @param iterations The number of iterations performed (output).
 * @param converged Boolean flag indicating whether the method converged (output).
 */
void jacobi_eigensolver(const arma::mat &A, double eps, arma::vec &eigenvalues, arma::mat &eigenvectors, const int maxiter, int &iterations, bool &converged);

#endif