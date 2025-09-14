#include "utils.hpp"


double max_offdiag_symmetric(const arma::mat &A, int &k, int &l){
    int N = A.n_rows;

    if(N != A.n_cols){
        std::cout << "Input matrix A for 'max_offdiag_symmetric' must be a square matrix, instead: (";
        std::cout << N << ", " << A.n_cols << std::endl;

        return 0;
    }

    double max = 0;
    for(int i=1; i<N; i++){
        for(int j=0; j<i; j++){
            if(std::abs(A(i,j)) > max){ // Comparing to current maximum
                max = std::abs(A(i,j));
                k = i; l = j;
            }
        }
    }

    return max;
}