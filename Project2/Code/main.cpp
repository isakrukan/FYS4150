#include <iostream>
#include <string>
#include <fstream>
#include "arg_parser.hpp"
#include "utils.hpp"
#include "jacobi_eigensolver.hpp"
#include "problems.hpp"


int main(int argc, char *argv[])
{
    Args args = parse_args(argc, argv);

    // -------------
    // Problem 5:
    // -------------

    if (args.run_problem_5)
    {
        problem_5(args.N_max, args.tol, args.maxiter, args.outfile);
        std::cout << "\nData for Problem 5 written to " << args.outfile << "\n";
    }

    // -------------
    // Problem 6:
    // -------------
    if (args.run_problem_6)
    {
        problem_6(args.n_steps, args.tol, args.maxiter, args.outfile);
        std::cout << "\nData for Problem 6 written to " << args.outfile << "\n";
    }

    return 0;
}