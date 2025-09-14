#include "triDag.hpp"
#include <stdexcept>
#include <cmath> 

TriDag::TriDag(double h, int N):
    a_fill(-1/(h*h)), d_fill(2/(h*h)), N(N), A(N, N, arma::fill::zeros){
    create_matrix();
}

void TriDag::create_matrix(){
    // Perhaps redundant to use this->, I am doing this for my own understanding.

    this->A(0,0) = this->d_fill;
    this->A(0,1) = this->a_fill;
    for(int i=1; i<this->N-1; i++){
        this->A(i,i+1) = this->a_fill;
        this->A(i,i) = this->d_fill;
        this->A(i,i-1) = this->a_fill;
    }
    this->A(N-1,N-1) = this->d_fill;
    this->A(N-1,N-2) = this->a_fill;
}

void TriDag::compute_eigenvalues(){
    arma::eig_sym(this->eigenvalues, this->eigenvectors, this->A);
    // Normalizing:
    this->eigenvalues = arma::normalise(this->eigenvalues);
    this->eigenvectors = arma::normalise(this->eigenvectors);
}

void TriDag::print(int max){

    if(this->N > max){
        std::cout << "Sorry, I won't print a matrix of size " << this->N << ", and I am not as advanced that I can skip rows..." << std::endl;
    }
    else{
        std::cout << "[";
        for(int i=0; i<N-1; i++){
            for(int j=0; j<N-1; j++){
                std::cout << this->A(i,j) << " ";
            }
            std::cout << this->A(i,N-1) << std::endl; 
        }

        for(int j=0; j<N-1; j++){
            std::cout << this->A(N-1,j) << " ";
        }
        std::cout << this->A(N-1,N-1) << "]" << std::endl; 
    }

}

void analytic_solution(arma::vec &eigenvalues, arma::mat &eigenvectors, double a, double d, int N){
    
    eigenvalues.set_size(N);
    eigenvectors.set_size(N,N);

    for(int j=0; j<N; j++){
        eigenvalues(j) = d + 2*a*std::cos((j+1)*arma::datum::pi / (N+1));
        for(int k=0; k<N; k++){
            eigenvectors(j, k) = std::sin((k+1)*(j+1)*arma::datum::pi / (N+1));
        }
    }

    eigenvalues = arma::normalise(eigenvalues);
    eigenvectors = arma::normalise(eigenvectors);
}