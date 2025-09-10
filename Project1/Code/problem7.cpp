#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip>
#include <cmath>

void change_b_and_g(std::vector<double> &b, std::vector<double> &g, const std::vector<double> &a, const std::vector<double> &c){
    // Changing the vectors b and g by reference using the Thomas algorithm. The vectors a and c remain constant.
    int n = b.size();
    
    for(int j=1; j<n; j++){
        b[j] = b[j] - a[j] * c[j-1]/b[j-1];
        g[j] = g[j] - a[j] * g[j-1]/b[j-1];
    }

}

double f_func(double x){
    return 100*std::exp(-10*x);
}

std::vector<double> general_algorithm(const std::vector<double> &a, 
                                            std::vector<double> &b, 
                                      const std::vector<double> &c, 
                                            std::vector<double> &g){
    change_b_and_g(b, g, a, c);
    int n = g.size();
    std::vector<double> v(n);

    v[n-1] = g[n-1]/b[n-1];
    for(int j=n-2; j>=0; j--){
        v[j] = (g[j] - c[j]*v[j+1])/b[j];
    }
    return v;
                                            }

void write_to_file(std::ofstream &ofile, const std::vector<double> &x, const std::vector<double> &v, double v0, double vN, int n_decimals=15){
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
}

int main(){
    std::vector<int> ns = {10-2, 100-2, 1000-2, 100000-2};
    int N = ns.size();

    double start = 0; double end = 1;

    // Creating an output file stream
    std::ofstream ofile;
    std::string filename = "problem7.txt";
    ofile.open(filename);

    // Iterating through every ns and applying general algorithm:
    for(int i=0; i<N; i++){

        std::cout << "Beginning with n = " << ns[i] << std::endl;
        // Initializing vectors:
        std::vector<double> a(ns[i]-1);
        std::vector<double> b(ns[i]);
        std::vector<double> c(ns[i]-1);
        std::vector<double> g(ns[i]);
        std::vector<double> x(ns[i]+2);
        
        double v0 = 0; double vN = 0; // Boundary conditions

        // Filling vectors with values:
        double step_size = (end-start)/(ns[i]+1);
        double h = (end-start) / (ns[i]-1);
        x[0] = start;
        for(int j=0; j<ns[i]-1; j++){

            x[j+1] = start + (j+1)*step_size;
            a[j] = -1; b[j] = 2; c[j] = -1;
            g[j] = std::pow(h, 2)*f_func(x[j+1]);
        }
        x[ns[i]] = start + (ns[i])*step_size;
        b[ns[i]-1] = 2;
        
        // Boundary values are special
        g[0] += v0;
        x[ns[i]+1] = start + (ns[i]+1)*step_size;
        g[ns[i]-1] = std::pow(h, 2)*f_func(x[ns[i]]) + vN;

        // Applying General Algorithm:
        std::vector<double> v = general_algorithm(a, b, c, g);

        // Writing to file:
        write_to_file(ofile, x, v, v0, vN);
        std::cout << "Complete with n = " << ns[i] << std::endl;
    }
    // Closing the output file
    ofile.close();
}