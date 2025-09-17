

#include "arg_parser.hpp"

Args parse_args(int argc, char *argv[])
{
    Args args;

    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];

        //
        if (arg == "--outfile" && i + 1 < argc)
        {
            args.outfile = argv[++i];
        }
        else if (arg == "--test")
        {
            args.run_tests = true;
        }
        else if (arg == "--problem5")
        {
            args.run_problem_5 = true;
        }
        else if (arg == "--problem6")
        {
            args.run_problem_6 = true;
        }
        else if (arg == "--tol" && i + 1 < argc)
        {
            args.tol = std::stod(argv[++i]);
        }
        else if (arg == "--n_steps" && i + 1 < argc)
        {
            args.n_steps = std::stoi(argv[++i]);
        }
        else if (arg == "--N_max" && i + 1 < argc)
        {
            args.N_max = std::stoi(argv[++i]);
        }
        else if (arg == "--maxiter" && i + 1 < argc)
        {
            args.maxiter = std::stoi(argv[++i]);
        }
        else
        {
            std::cerr << "Unknown argument: " << arg << "\n";
            exit(1);
        }
    }

    return args;
}