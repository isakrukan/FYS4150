# FYS4150 project 2

Implementing Jacobi's rotation method.

## Description
See [FYS3150/project2](https://anderkve.github.io/FYS3150/book/projects/project2.html).

## Code Structure and Explanation 
We have made an overview of the code structure and content in [doc](https://github.com/isakrukan/FYS4150/blob/main/Project2/docs/doc.pdf). This is presumably a way too detailed description for this project, and the code in this project is perhaps best understood by simply reading the comments in the explicit code. (See [include](https://github.com/isakrukan/FYS4150/tree/main/Project2/Code/include), [plot_eigen.py](https://github.com/isakrukan/FYS4150/blob/main/Project2/Code/plot_eigen.py) and [plot_iter.py](https://github.com/isakrukan/FYS4150/blob/main/Project2/Code/plot_iter.py).) 

The code overview in  [doc](https://github.com/isakrukan/FYS4150/blob/main/Project2/docs/doc.pdf) is created using [doxygen](https://www.doxygen.nl/), and we have made use of artificial intelligence (ChatGPT) when learning how to use this tool. To generate a new doc-file, navigate do docs and run
```
make all
```

### Executables/Makefile
The project can be built by navigating to the Code folder and running 
```
make all
```
The Makefile builds two executables, `main` and `test`, which are placed in the `build` folder. After building, all object files are deleted and all tests are executed automatically. The Makefile does differentiate between Windows and Mac/Linux, in particular, on Windows (NB!) it assumes Armadillo is installed via vcpkg in a specific location.

## Problem 2-3
A more detailed description is provided in [project2](https://github.com/isakrukan/FYS4150/blob/main/Project2/main.pdf). These problems are implemented as the default tests ran when executing Makefile. 

## Problem 5-6
Uses an argument parser to change parameters (`arg_parser.cpp`) 

### Available Parser Arguments for main.exe:
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
