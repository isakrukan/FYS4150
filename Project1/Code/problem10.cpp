#include <iostream> 
#include <vector> 
#include <fstream> 
#include <iomanip>
#include <cmath>
#include <functional>
#include <chrono>

// From problem 7:
void change_b_and_g(std::vector<double> &b, std::vector<double> &g, const std::vector<double> &a, const std::vector<double> &c){
    // Changing the vectors b and g by reference using the Thomas algorithm. The vectors a and c remain constant.
    int n = b.size();
    
    for(int j=1; j<n; j++){
        b[j] = b[j] - (a[j-1] / b[j-1]) * c[j-1];
        g[j] = g[j] - a[j-1] * g[j-1]/b[j-1];
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


// From problem 9:
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


int compare_with_reapeated_runs(std::vector<int> ns, int N_reapted_runs, 
                                std::vector<double> &times_general_algo, 
                                std::vector<double> &times_special_algo){
    // Runs "N_reapeated_runs" with n_steps \in "ns" and makes a averaged version of "times_general_algo" and 
    // "times_special_algo".

    int N = ns.size();

    for(int k=0; k<N_reapted_runs; k++){
        // Iterating through every ns and applying general algorithm:
        for(int i=0; i<N; i++){

            ///////// General Algorithm
            // Iterating through every ns and applying general algorithm:
            auto t_start_general = std::chrono::high_resolution_clock::now();

            // Initializing vectors:
            std::vector<double> a(ns[i]-1);
            std::vector<double> b(ns[i]);
            std::vector<double> c(ns[i]-1);
            std::vector<double> g(ns[i]);
            std::vector<double> x(ns[i]+2);
            
            double v0 = 0; double vN = 0; // Boundary conditions
            double end = 1; double start = 0; // Boundary conditions

            // Filling vectors with values:
            double h = (end-start) / (x.size()-1);
            x[0] = start;
            for(int j=0; j<ns[i]-1; j++){

                x[j+1] = start + (j+1)*h;
                a[j] = -1; b[j] = 2; c[j] = -1;
                g[j] = (h*h)*f_func(x[j+1]);
            }
            x[ns[i]] = start + (ns[i])*h;
            b[ns[i]-1] = 2;
            
            // Boundary values are special
            g[0] += v0;
            x[ns[i]+1] = start + (ns[i]+1)*h;
            g[g.size()-1] = (h*h)*f_func(x[x.size()-1]) + vN;

            // Applying General Algorithm:
            general_algorithm(a, b, c, g);

            auto t_end_general = std::chrono::high_resolution_clock::now();
            times_general_algo[i] += (std::chrono::duration<double>(t_end_general - t_start_general).count()) / N;  // Divides by N to compute average
        

            ///////// Special Algorithm
            auto t_start_special = std::chrono::high_resolution_clock::now();
            // Initializing vectors:
            std::vector<double> v_special(ns[i]);
            std::vector<double> x_special(ns[i]+2);

            // Applying Special Algorithm:
            special_algorithm(v_special,x_special);

            auto t_end_special = std::chrono::high_resolution_clock::now();
            times_special_algo[i] += (std::chrono::duration<double>(t_end_special - t_start_special).count()) / N;  // Divides by N to compute average
        }
    }

    return 0;
}
int main(){
    std::vector<int> ns = {10, 100, 1000, 10000, 100000, 1000000};
    int N = ns.size();

    std::vector<double> times_general_algo(N,0);
    std::vector<double> times_special_algo(N,0);

    int N_repeated_runs = 100;

    int success_ = compare_with_reapeated_runs(ns, N_repeated_runs, times_general_algo, times_special_algo);

    if(success_){
        std::cout << "Complete!" << std::endl;
    }

    // Writing results:

    int n_decimals=15;
    std::ofstream ofile;
    ofile.open("problem10.txt");

    ofile << "general, special, n" << int(N+2) << std::endl; // Header

    for(int i=0; i<N; i++){
        ofile << std::setprecision(n_decimals) << std::scientific << times_general_algo[i];
        ofile << ", ";
        ofile << std::setprecision(n_decimals) << std::scientific << times_special_algo[i];
        ofile << ", ";
        ofile << std::setprecision(n_decimals) << std::scientific << ns[i] << std::endl;
        }
}