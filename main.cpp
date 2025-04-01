#include "Problem.hpp"
#include "NSGA.hpp"
#include <chrono>
#include <iostream>

#include "Debug.hpp"
int main(int argc, char **argv) {
#if EXPORT
    constexpr export_type type_of_export=SIMPLE;
    Export exporter;
    const std::string directory=Export::create_directory();
#endif


    const ZDT3 problem;
    constexpr int seed=0;
    double hypervolume=0;
    std::chrono::microseconds execution_time{};

    for (int run=1;run<NOISE+1;run++) {
    NSGA nsga_solver(&problem, POPULATION_SIZE,GENERATION_COUNT,CROSSOVER_ALPHA,
        MUTATION_DISTRIBUTION,MUTATION_PROBABILITY,seed);
    const auto start = std::chrono::high_resolution_clock::now();
#if EXPORT
        hypervolume=hypervolume+nsga_solver.run(&exporter,run);
#else
        hypervolume=hypervolume+nsga_solver.run(run);
#endif
    const auto stop = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        execution_time=execution_time+duration;
#if EXPORT
        exporter.export_data(duration,run,type_of_export,&problem,POPULATION_SIZE,GENERATION_COUNT,
            CROSSOVER_ALPHA,MUTATION_DISTRIBUTION,MUTATION_PROBABILITY,seed,nsga_solver.Objective_space,directory);
#endif
#if DEBUG
    Debug::debug_exec_time(duration);
#endif
    }
#if EXPORT
    exporter.plot_data(NOISE,type_of_export,directory);
#endif
    std::cout<<hypervolume/NOISE<<std::endl;
    std::cout<<std::chrono::duration_cast<std::chrono::microseconds>(execution_time).count()/NOISE<<std::endl;
}
