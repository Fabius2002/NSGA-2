#if DEBUG

#ifndef DEBUG_HPP
#define DEBUG_HPP
#include <chrono>
struct Debug {

    static void debug_init(int gen, int generation_max, double hv, int pareto_size, int population_size);
    static void debug_gen(int gen, int generation_max, double hv, int pareto_size, int population_size);
    static void debug_final(int run_number, const Problem *problem, int generation_max, int population_size,
        double mutation_distribution, double mutation_probability, double crossover_alpha);

    static void debug_exec_time(std::chrono::duration<long, std::ratio<1, 1000000> > time);
};
#endif //DEBUG_HPP
#endif