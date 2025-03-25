#include "Problem.hpp"
#include "NSGA.hpp"
#include <iostream>
#include <vector>
#include <chrono>
int main(int argc, char **argv) {
    const ZDT3 problem;
    int population_size = 10;
    int generation_count = 100;
    double crossover_alpha = 0.5;
    double mutation_distribution = 20;
    double mutation_probability = 0.5;



    NSGA nsga_solver(&problem, population_size,generation_count,crossover_alpha,mutation_distribution,mutation_probability);
    auto start = std::chrono::high_resolution_clock::now();
    nsga_solver.run();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    nsga_solver.export_data(duration);
}
//20000000
//5000000


//52832,