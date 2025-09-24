# FYS4150 project 2

HEI ISAK!
HEI MAGNUS!

See docs/doc.pdf for a (way too) detailed description of the code structure of this project.

# Changes

## Makefile
Added a makefile. 

The project can be built using
```
make all
```
The executables (`main`, `test`) end up in the `build` folder.
This also runs the tests immediately.

## Problem 5-6
Made code for project 5-6 (`main.cpp`)

Uses an argument parser to change parameters (`arg_parser.cpp`) 

(Might be unnecessarily complicated)
### The possible arguments are:
```
--outfile <filename> : Specify output file name (default: build/outfile.csv)
--test               : Run tests

--problem5           : Run problem 5
--N_max     <value>  : Set maximum matrix size in Problem 5 (default: 100)

--problem6           : Run problem 6
--n_steps   <value>  : Set number of steps in problem 6(default: 10)

--tol       <value>  : Set tolerance in Jacobi alg. (default: 1e-8)
--maxiter   <value>  : Set maximum iterations in Jacobi alg. (default: 10000)
 ```

### Example usage:

```bash
./build/main --problem5 --N_max 150 --maxiter 100000 --outfile output/problem5.csv   
```
```bash
./build/main --problem6 --n_iter 100 --maxiter 10000 --outfile output/problem6-n10.csv   
```

## Plots:
Python scripts `plot_iter.py` and `plot_eigen.py` produce figures for problem 5 and 6 respectively.
