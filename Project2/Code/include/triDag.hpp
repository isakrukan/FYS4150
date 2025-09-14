#include <armadillo> 

class TriDag{

// Tridiagonal matrix of the form (a,d,a) with a = -1/h^2, d = 2/h^2 (see constructor)

private:
    double a_fill;
    double d_fill;
    int N;

    void create_matrix();  // Creates tridiagonal matrix

public:

    // Parameters
    arma::mat A; 
    arma::vec eigenvalues;
    arma::mat eigenvectors;

    // Constructor
    TriDag(double h, int N);

    // Function(s)
    void compute_eigenvalues(); // Function for computing eigenvalues using arma::eig_sym

    void print(int max=25);
};


void analytic_solution(arma::vec &eigenvalues, arma::mat &eigenvectors, double a, double d, int N);