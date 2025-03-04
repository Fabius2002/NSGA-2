#ifndef NSGA_H
#define NSGA_H
#include "Problem.hpp"
#include <vector>
#include <random>

struct NSGA {
    std::vector<double> Decision_space;
    std::vector<double> Objective_space;
    const int population_size;
    const Problem* problem;
    std::vector<double> crowding_distance;
    std::vector<int> rank;
    std::mt19937_64 mt;
    NSGA(const Problem* problem, const int population_size,int seed=0):population_size(population_size),problem(problem),mt((seed == 0) ? std::random_device{}() : seed) {
        Decision_space=std::vector<double>(population_size*problem->get_Decision_space_dim()*2);
        Objective_space=std::vector<double>(population_size*problem->get_Objective_space_dim()*2);
        crowding_distance=std::vector<double>(population_size*2);
        rank=std::vector<int>(population_size*2);
    };
    ~NSGA() = default;
    void run(int generation_max);
    void init_population();
    void crowding_distance_calculation(const std::vector<int>& front);
    [[nodiscard]] int binary_tournament_selection();
    void generate_offspring_population(double alpha, double distribution);
    void export_data();

};
#endif
