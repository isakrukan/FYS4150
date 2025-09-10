#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip>
#include <cmath>
#include <functional>

double f_func(double x){
    return 100*std::exp(-10*x);
}

int special_algorithm(std::vector<double> &v, std::vector<double> &x){
    // Specialized algorithm. Assumes a = (-1, ..., -1) and c = (-1, ..., -1), uses f_func as source term for 
    // Poisson equation. Changes v and x by reference.

    int n = v.size();
    std::vector<double> g(n);
    std::vector<double> b(n,2);
    
    double v0 = 0; double vN = 0; // Boundary conditions
    double h = 1. / (x.size()-1);

    // Filling vectors with values and forward substitution:
    x[1] = h;
    g[0] = (h*h) * f_func(x[1]);
    for(int j=1; j<n; j++){
        x[j+1] = (j+1)*h;
        b[j] = 2 - 1./b[j-1];
        g[j] = (h*h)*f_func(x[j+1]) +  g[j-1]/b[j-1];
    }
    x[n+1] = (n+1)*h;
    
    // Backward substitution:
    v[n-1] = g[n-1]/b[n-1];
    for(int j=n-2; j>=0; j--){
        v[j] = (g[j] + v[j+1])/b[j];
    }
    return 0;
}

int write_to_file(std::ofstream &ofile, const std::vector<double> &x, const std::vector<double> &v, double v0, double vN, int n_decimals=15){
    // Writes "x" and "v" to "ofile" (NB! Does not close file). 
    // Uses "n_decimals" number of decimal points

    // Writing to file
    int n = v.size();
    ofile << "x, v, " << int(n+2) << std::endl; // Header

    ofile << std::setprecision(n_decimals) << std::scientific << x[0];
    ofile << ", ";
    ofile << std::setprecision(n_decimals) << std::scientific << v0 << std::endl;
    for(int i=0; i<n; i++){
        ofile << std::setprecision(n_decimals) << std::scientific << x[i+1];
        ofile << ", ";
        ofile << std::setprecision(n_decimals) << std::scientific << v[i] << std::endl;
    }

    ofile << std::setprecision(n_decimals) << std::scientific << x[n+1];
    ofile << ", ";
    ofile << std::setprecision(n_decimals) << std::scientific << vN << std::endl;
    
    return 0;
}

int main(){
    std::vector<int> ns = {10-2, 100-2, 1000-2, 100000-2};
    int N = ns.size();
    int success1 = 1; int success2 = 1;

    // Creating an output file stream
    std::ofstream ofile;
    std::string filename = "problem9.txt";
    ofile.open(filename);

    // Iterating through every ns and applying general algorithm:
    for(int i=0; i<N; i++){

        std::cout << "Beginning with n = " << ns[i] << std::endl;
        // Initializing vectors:
        std::vector<double> v(ns[i]);
        std::vector<double> x(ns[i]+2);

        // Applying Special Algorithm:
        success1 = special_algorithm(v,x);

        // Writing to file:
        success2 = write_to_file(ofile, x, v, 0, 0);
        if(success1==success2 and success1 == 0) {
            std::cout << "Complete with n = " << ns[i] << std::endl;
        }

        else{
            std::cout << "Failed with n = " << ns[i] << std::endl;
        }
    }
    // Closing the output file
    ofile.close();
}