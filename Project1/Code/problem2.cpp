#include <iostream> 
#include <vector> 
#include <cmath> 
#include <fstream> 
#include <iomanip>

// using namespace std;

std::vector<double> linspace(double start, double end, int size=50){
    // Minimalistic version of np.linspace 

    std::vector<double> x(size);
    double step_size = (end - start)/(size-1);

    for(int i=0; i<size; i++){
        x[i] = start + i*step_size;
    }
    return x;
}

std::vector<double> u(std::vector<double> x){
    // Returns u(x) = 1 - (1 - e^{-10})x - e^{-10x} for a given vector x

    int size = x.size();
    std::vector<double> u_vector(size);
    for(int i=0; i<size; i++){
        u_vector[i] = 1 - (1 - std::exp(-10))*x[i] - std::exp(-10*x[i]);
    }
    return u_vector;
}

int write_u_to_file(std::ofstream &ofile, const int N, const int n_decimals=15){
    // Creates vector of size "N" x of values from 0 to 1, computes u(x) and writes to "filename". 
    // Uses "n_decimals" number of decimal points

    std::vector<double> x = linspace(0,1,N);
    std::vector<double> u_vector = u(x);

    // Writing to file
    ofile << "x, u, " << N << std::endl; // Header
    for(int i=0; i<N; i++){
        ofile << std::setprecision(n_decimals) << std::scientific << x[i];
        ofile << ", ";
        ofile << std::setprecision(n_decimals) << std::scientific << u_vector[i] << std::endl;
    }

    return 0;
}

int main(){
    std::vector<int> ns = {10, 100, 1000, 10000, 100000, 1000000, 10000000};
    std::string filename = "problem2.txt";

    // Creating an output file stream
    std::ofstream ofile;
    ofile.open(filename);

    // Writing to file
    for(int i=0; i<ns.size(); i++){
        std::cout << "2 x " << ns[i] << " data points written to " << filename << " complete." << std::endl;
        write_u_to_file(ofile, ns[i]);
    }

    // Close the output file
    ofile.close();
}