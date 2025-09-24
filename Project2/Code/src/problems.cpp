#include "problems.hpp"
#include "jacobi_eigensolver.hpp"
#include "triDag.hpp"
#include <armadillo>

void problem_5(double N_max, double tol, int maxiter, const std::string &outfile)
{
    arma::mat A;
    arma::vec eigvals;
    arma::mat eigvecs;

    int iterations;
    bool converged;

    std::ofstream ofile;
    ofile.open(outfile);

    // Write results for different N:
    for (int N = 5; N <= N_max; N += 5)
    {
        std::cout << "\rProcessing N = " << N << std::flush;

        double h = 1.0 / (N + 1);
        double d = 2 / (h * h);
        double a = -1 / (h * h);
        A = create_tridiagonal(N, a, d, a);

        jacobi_eigensolver(A, tol, eigvals, eigvecs, maxiter, iterations, converged);
        ofile << N << "," << iterations << "," << converged << "\n";

        // Stop if convergence not reached:
        if (not converged)
        {
            std::cout << "\nWarning: did not converge for N = " << N << ", terminating...\n";
            break;
        }
    }
    ofile.close();
}

void problem_6(int n_steps, double tol, int maxiter, const std::string &outfile)
{
    int N = n_steps - 1;
    double h = 1.0 / n_steps;
    double d = 2 / (h * h);
    double a = -1 / (h * h);

    arma::mat A = create_tridiagonal(N, a, d, a);
    arma::vec eigvals;
    arma::mat eigvecs;

    int iterations;
    bool converged;

    jacobi_eigensolver(A, tol, eigvals, eigvecs, maxiter, iterations, converged);

    if (not converged)
    {
        std::cout << "\nWarning: Solver did not converge";
    }
    std::ofstream ofile;
    ofile.open(outfile);
    ofile << eigvals.t() << "\n"
          << eigvecs;
    ofile.close();
}