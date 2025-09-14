#include "utils.hpp"
#include "triDag.hpp" 
#include <cassert>

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

int test_max_offdiag_symmetric(){
    int N = 4; double eps = 1e-15;
    arma::mat A(N, N, arma::fill::zeros);

    double x_1 = 0.7; double x_2 = 0.5;
    double diag = 1.;
    A(2,1) = -x_1; A(1,2) = -x_1;
    A(3,1) = x_2; A(1,3) = x_2;
    A(0,0) = diag; A(1,1) = diag; A(2,2) = diag; A(3,3) = diag;

    int k; int l;
    double max = max_offdiag_symmetric(A, k, l);

    assert(std::abs(max-x_1) < eps);
    assert(k == 2); assert(l == 1);

    return 0;
}

int main(){
    
    test_TriDag();
    test_max_offdiag_symmetric();

    // To compile: 
    /*
    g++ tests/test.cpp src/triDag.cpp src/utils.cpp `
    -I include `
    -I C:/vcpkg/installed/x64-mingw-dynamic/include `
    -L C:/vcpkg/installed/x64-mingw-dynamic/lib `
    -o test `
    -larmadillo
    */ 
}