#include "Problem.hpp"
#include "NSGA.hpp"
#include <iostream>
#include <vector>
#include <chrono>
int main() {
    // Define the problem (SCH1)
    SCH1 problem;

    // Define population size
    constexpr int population_size = 10 ; // Larger population size

    // Initialize the NSGA solver
    NSGA nsga_solver(&problem, population_size);
    auto start = std::chrono::high_resolution_clock::now();
    nsga_solver.run(100);
    auto stop = std::chrono::high_resolution_clock::now();
    for (int i=0;i<population_size;i++) {
        std::cout<<nsga_solver.Decision_space[i] << " " << std::endl ;
    }
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "time taken :" << duration.count();
    nsga_solver.export_data();
}
//20000000
//5000000


//52832,