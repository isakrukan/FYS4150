#ifndef ARG_PARSER_CPP
#define ARG_PARSER_CPP

#include <string>
#include <iostream>

/**
 * @brief Struct to hold command-line arguments.
 */
struct Args
{
    std::string outfile = "build/outfile.csv";
    bool run_tests = false;
    bool run_problem_5 = false;
    bool run_problem_6 = false;
    double tol = 1e-14;
    int n_steps = 10;
    int N_max = 100;
    int maxiter = 10000;
};

/** @addtogroup StandAloneFunctions
 * @{
 */

/**
 * @brief Function for parsing command-line arguments.
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return Args struct containing the parsed values.
 */
Args parse_args(int argc, char *argv[]);

#endif

/** @} */