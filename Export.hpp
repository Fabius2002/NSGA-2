#if EXPORT
#ifndef EXPORT_HPP
#define EXPORT_HPP
#include <chrono>
#include <vector>

#include "Problem.hpp"
enum export_type{SIMPLE,HYPERVOLUME_COMPARISON};
struct Export {
    std::vector<double> hypervolume;
    void stash_hypervolume(double hv);
    void export_data(std::chrono::microseconds time, int runs, export_type type, const Problem *problem, int population_size, int generation_max,
                     double crossover_alpha, double mutation_distribution, double mutation_probability,int seed, const std::vector<double>
                     &Objective_space,const std::string& directory);
    static std::string create_directory();
    void plot_data(int runs, export_type type,const std::string& directory);
    void export_hypervolume(const int runs,const std::string& directory);
};

#endif
#endif
