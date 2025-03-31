#include "Problem.hpp"
#if DEBUG
#include "Debug.hpp"
#include <iomanip>
#include <iostream>

void Debug::debug_init(const int gen,const int generation_max,const double hv,const int pareto_size,const int population_size) {
    std::cout<<std::string(57,'-')<<std::endl;
    std::cout<<"| Generation | Hypervolume | Pareto_count | evaluations |"<<std::endl;
    std::cout<<std::string(57,'-')<<std::endl;
    std::cout<<"|"<<std::setw(7)<<gen <<"/"<<generation_max<< " | "
        <<std::setw(11)<<hv <<" | "<<std::setw(12)<<pareto_size <<" | "
        <<std::setw(11)<<gen*population_size <<" | "<<std::endl;
}

void Debug::debug_gen(const int gen, const int generation_max, const double hv, const int pareto_size, const int population_size) {
    std::cout<<"|"<<std::setw(7)<<gen*1 <<"/"<<generation_max<< " | "
        <<std::setw(11)<<hv <<" | "<<std::setw(12)<<pareto_size <<" | "
        <<std::setw(11)<<(gen+1)*population_size <<" | "<<std::endl;
}
void Debug::debug_final(const int run_number,const Problem* problem,const int generation_max, const int population_size,
    const double mutation_distribution,const double mutation_probability,const double crossover_alpha) {
    std::cout<<std::string(57,'-')<<std::endl;
    std::cout<<run_number<<". Run optimizing "<<problem->debug_output_prob() << " for " <<generation_max
    <<" generations with a population size of " << population_size <<", mutation probability of "
    <<mutation_probability<<", and a mutation distribution of "<<mutation_distribution<< " and a crossover alpha of "<< crossover_alpha <<std::endl;
}

void Debug::debug_exec_time(std::chrono::duration<long, std::ratio<1, 1000000>> time) {
    std::cout << "Executed in :" << time << std::endl;
}
#endif
