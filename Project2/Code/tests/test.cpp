#include "utils.hpp"
#include "triDag.hpp"
#include "jacobi_eigensolver.hpp"
#include "utils.hpp"
#include <cassert>

/**
 * @defgroup Tests Tests
 * @brief Various tests of our code.
 */
/**
 * @brief Tests the implementation of the tridiagonal matrix in @ref triDag.
 */
int test_TriDag(){
    
    double eps = 1e-14; // Error tollerance
    int N = 6;
    double h = 1./N;
    double a = -1/(h*h); double d = 2/(h*h);

    arma::vec analytic_eigenvalues; 
    arma::mat analytic_eigenvectors;
    analytic_solution(analytic_eigenvalues, analytic_eigenvectors, a, d, N);
    
    TriDag A(h, N);
    // A.print();

    A.compute_eigenvalues();
    arma::vec numerical_eigenvalues = A.eigenvalues; 
    arma::mat numerical_eigenvectors = A.eigenvectors;

    double error_eigenvalues = 0;
    
    for(int j=0; j<N; j++){

        error_eigenvalues += std::abs(analytic_eigenvalues(j) - numerical_eigenvalues(j));
    }

    assert(error_eigenvalues < eps);
    return 0;
}

/**
 * @brief Tests that the function @ref utils::max_offdiag_symmetric correctly computes the maximum (in absolute value) element of a 
 * symmetric matrix and updates a given pair of row and column indicies.
 */
int test_max_offdiag_symmetric(){
    int N = 4; double eps = 1e-15;
    arma::mat A(N, N, arma::fill::zeros);

    double x_1 = -0.7; double x_2 = 0.5;
    double diag = 1.;
    A(2,1) = x_1; A(1,2) = x_1;
    A(3,1) = x_2; A(1,3) = x_2;
    A(0,0) = diag; A(1,1) = diag; A(2,2) = diag; A(3,3) = diag;

    int k; int l;
    double value = max_offdiag_symmetric(A, k, l);

    assert(std::abs(value-x_1) < eps);
    assert(k == 2); assert(l == 1);

    return 0;
}

/**
 * @brief Tests the implementation of Jacobi's iteration method in @ref jacobi_eigensolver.
 * 
 * @return int 
 */
int test_jacobi()
{
    // Initialize test matrix:
    int N = 6;
    double h = 1.0 / (N + 1);
    double d = 2 / (h * h);
    double a = -1 / (h * h);
    arma::mat A = create_tridiagonal(N, a, d, a);

    // Compute eigenvectors and eigenvalues analytically and numerically:
    arma::vec expected_vals;
    arma::mat expected_vecs;
    analytic_solution(expected_vals, expected_vecs, a, d, N);

    arma::mat computed_vecs;
    arma::vec computed_vals;

    int maxiter = 100;
    int iterations;
    bool converged;

    jacobi_eigensolver(A, 1e-8, computed_vals, computed_vecs, maxiter, iterations, converged);

    // To compare eigenvalues/vectors, sort by eigenvalue:
    arma::uvec sort_idx;

    sort_idx = arma::sort_index(expected_vals);
    expected_vals = expected_vals.elem(sort_idx);
    expected_vecs = expected_vecs.cols(sort_idx);

    sort_idx = arma::sort_index(computed_vals);
    computed_vals = computed_vals.elem(sort_idx);
    computed_vecs = computed_vecs.cols(sort_idx);

    // Check equality.
    double tol = 1e-10;
    bool passed = true;

    if (not arma::approx_equal(expected_vals, computed_vals, "absdiff", tol))
    {
        passed = false;
    }

    for (int i = 0; i < N; i++)
    {
        // Check equality, up to a sign difference
        // (assumes eigenvectors are normalized)
        bool equal = arma::approx_equal(expected_vecs.col(i), computed_vecs.col(i), "absdiff", tol);
        bool mirrored = arma::approx_equal(expected_vecs.col(i), -computed_vecs.col(i), "absdiff", tol);
        
        assert(equal or mirrored);
    }
    return 0;
}

int main(){
    test_TriDag();
    test_max_offdiag_symmetric();
    test_jacobi();
}