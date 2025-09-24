#include <armadillo> 


/**
 * @brief Class representing a tridiagonal matrix, i.e. an matrix of the form
 * \f[
 * A = \begin{pmatrix}
 *  a & c & 0 & \cdots & 0 \\
 *  b & a & c & \cdots & 0 \\
 *  0 & b & a & \ddots & \vdots \\
 *  \vdots & \ddots & \ddots & \ddots & c \\
 *  0 & \cdots & 0 & b & a
 * \end{pmatrix},
 * \f]
 * where \f(b=c=-1/h^2\f) and \f(a=2/h^2\f).
 * @param A Armadillo matrix.
 * @param eigenvalues Armadillo vector for the eigenvalues of the matrix A.
 * @param eigenvectors Armadillo vector for the eigenvectors of the matrix A.
 * @see TriDag
 */
class TriDag{
private:
    double a_fill;
    double d_fill;
    int N;

    void create_matrix();  // Creates tridiagonal matrix

public:
    arma::mat A; 
    arma::vec eigenvalues;
    arma::mat eigenvectors;

    /**
     * @brief Creates a new tridiagonal object.
     * 
     * @param h Stepsize, defining the diagonals of the tridiagonal matrix, see general @ref TriDag "description".
     * @param N Size of matrix. 
     */
    TriDag(double h, int N);

    
    /**
     * @brief Computes the eigenvalues of the tridiagonal matrix using arma::eig_sym.
     * 
     */
    void compute_eigenvalues(); 

    /**
     * @brief Prints the elements of the tridiagonal matrix.
     * 
     * @param max Only prints matrix if the size of the matrix is less than or equal to max.
     */
    void print(int max=25);    
};

/** @addtogroup StandAloneFunctions 
 * @{
*/
/**
 * @brief Gives the analytic solution for the eigenvalues and eigenvectors of \f(A\vec{v} = \lambda \vec{v}\f), 
 * where \f(A\f) is a tridiagonal matrix(a,d,a).
 * 
 * @param eigenvalues Armadillo vector for eigenvalues.
 * @param eigenvectors Armadillo vector for eigenvectors.
 * @param a Upper and lower diagonal of matrix.
 * @param d Diagonal of matrix.
 * @param N Size of matrix.
 */
void analytic_solution(arma::vec &eigenvalues, arma::mat &eigenvectors, double a, double d, int N);
/** @} */