#ifndef ARG_PARSER_CPP
#define ARG_PARSER_CPP

#include <string>
#include <iostream>

/**
 * @brief Struct to hold command-line arguments.
 */
struct Args
{
    std::string outfile = "build/outfile.csv";  ///< Where and what to store outfile, associated to given problem (5 or 6).
    bool run_tests = false;                     ///< If true, runs the tests defined in "tests/".
    bool run_problem_5 = false;                 ///< If true, runs problem 5.
    bool run_problem_6 = false;                 ///< If true, runs problem 6.
    double tol = 1e-14;                         ///< Tolerance when running Jacobi's rotation method.
    int n_steps = 10;                           ///< Number of steps when running Jacobi's rotation method.
    int N_max = 100;                            ///< Number of different sizes for the matrix A in Jacobi's rotation method (problem 5).
    int maxiter = 10000;                        ///< Maximum number of iterations when running Jacobi's method.
};


/**
 * @brief Method for parsing command-line arguments.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Args struct containing the parsed values.
 */
Args parse_args(int argc, char *argv[]);

#endif
