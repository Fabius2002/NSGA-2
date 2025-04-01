#include "Problem.hpp"
#include "NSGA.hpp"
#include <chrono>
#include <iostream>

#include "Debug.hpp"
int main(int argc, char **argv) {
#if EXPORT
    constexpr export_type type_of_export=HYPERVOLUME_COMPARISON;
    Export exporter;
    const std::string directory=Export::create_directory();
#endif


    const ZDT3 problem;
    constexpr int seed=0;
    const std::vector<int> Population_size={100,18};
    const std::vector<int> Generation_count={100,19};
    const std::vector<float> Crossover_alpha={0.5,0.7783892363365335};
    const std::vector<float> Mutation_Distribution={20,8};
    const std::vector<float>Mutation_Probability={0.5,0.2896296405458124};
    for (int run=1;run<Population_size.size()+1;run++) {
    NSGA nsga_solver(&problem, Population_size[run-1],Generation_count[run-1],Crossover_alpha[run-1],
        Mutation_Distribution[run-1],Mutation_Probability[run-1],seed);
    const auto start = std::chrono::high_resolution_clock::now();
#if EXPORT
        nsga_solver.run(&exporter,run);
#else
        nsga_solver.run(run);
#endif
    const auto stop = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
#if EXPORT
        exporter.export_data(duration,run,type_of_export,&problem,Population_size[run-1],Generation_count[run-1],Crossover_alpha[run-1],
        Mutation_Distribution[run-1],Mutation_Probability[run-1],seed,nsga_solver.Objective_space,directory);
#endif
#if DEBUG
    Debug::debug_exec_time(duration);
#endif
    }
#if EXPORT
    exporter.plot_data(Population_size.size(),type_of_export,directory);
#endif
}
