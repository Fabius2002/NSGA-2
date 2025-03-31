#ifndef NSGA_H
#define NSGA_H
#include <chrono>
#include "Problem.hpp"
#include <vector>
#include <random>

#if EXPORT
#include "Export.hpp"
#endif

struct NSGA {
    std::vector<double> Decision_space;
    std::vector<double> Objective_space;
    const int population_size;
    const Problem* problem;
    std::vector<double> crowding_distance;
    std::vector<int> rank;
    std::mt19937_64 mt;
    const double mutation_distribution;
    const double mutation_probability;
    const double crossover_alpha;
    const int generation_max;
    NSGA(const Problem* problem, const int population_size,const int generation_max,const double crossover_alpha,
        const double mutation_distribution=20, const double mutation_probability=1,int seed=0)
        : population_size(population_size), problem(problem), mt((seed == 0) ? std::random_device{}() : seed),
          mutation_distribution(mutation_distribution),
          mutation_probability(mutation_probability), crossover_alpha(crossover_alpha), generation_max(generation_max) {
        Decision_space = std::vector<double>(population_size * problem->get_Decision_space_dim() * 2);
        Objective_space = std::vector<double>(population_size * problem->get_Objective_space_dim() * 2);
        crowding_distance = std::vector<double>(population_size * 2);
        rank = std::vector<int>(population_size * 2);
    };
    ~NSGA() = default;

#if EXPORT
    void run(Export* exporter,int run_number=1);
#else
    void run(int run_number=1);
#endif

    void init_population();
    void crowding_distance_calculation(const std::vector<int>& front);
    [[nodiscard]] int binary_tournament_selection();
    void generate_offspring_population(double alpha, double mutation_distribution, double mutation_probability);
    [[nodiscard]] double calculate_hypervolume_2d(const std::vector<int> &front) const;

};
#endif
