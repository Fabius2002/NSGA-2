#include <fstream>
#if EXPORT
#include "Export.hpp"
#include <iostream>
#include <ctime>
#include <filesystem>
#include <sstream>
std::string Export::create_directory() {
    const time_t sec=std::time(nullptr);
    tm *local_time=localtime(&sec);
    std::stringstream ss;
    ss<<std::put_time(local_time, "%d_%m %I:%M:%S");
    const std::string directory="../Runs/"+ss.str();
    std::filesystem::create_directory(directory);
    return directory;
}

void Export::plot_data(int runs, export_type type, const std::string &directory) {
    const std::string command = "/home/fabius/anaconda3/envs/NSGA2/bin/python ../plot/plot.py "+std::to_string(runs) + " " +std::to_string(type)+ " " +directory;
    int status2 = std::system(command.data());
}

void export_results(const Problem* problem,const int population_size, const int runs,
                    const std::vector<double>& Objective_space,const std::string& directory) {
    std::ofstream output(directory+"/results_"+std::to_string(runs)+".csv");
    for (int dim=0;dim<problem->get_Objective_space_dim();dim++) {
        output <<"x"<<dim+1;
        if (dim<problem->get_Objective_space_dim()-1) {
            output <<",";
        }
    }
    output << std::endl;
    for (int i=0;i<population_size;i++) {
        for (int dim=0;dim<problem->get_Objective_space_dim();dim++) {
            output << Objective_space[i*problem->get_Objective_space_dim()+dim] ;
            if (dim < problem->get_Objective_space_dim() - 1) output << ", ";
        }
        output << std::endl;
    }
    output.close();
}
void export_meta(const std::chrono::microseconds time, const int runs, const Problem *problem,
    const int population_size, const int generation_max, const double crossover_alpha, const double mutation_distribution,
    const double mutation_probability, const int seed,const std::string& directory) {
    std::ofstream output2(directory+"/meta_"+std::to_string(runs)+".txt");
    output2<< population_size << std::endl << generation_max << std::endl << mutation_distribution << std::endl << mutation_probability
        <<std::endl<<crossover_alpha<< std::endl << time << std::endl <<problem->debug_output_prob() <<std::endl << seed << std::endl;
    output2.close();
}

void Export::export_hypervolume(const int runs,const std::string& directory) {
    std::ofstream output(directory+"/hypervolume_"+std::to_string(runs)+".csv");
    output <<"hv"<< std::endl;
    for (double i : hypervolume) {
        output<<i << std::endl;
    }
    hypervolume.clear();
    output.close();
}
void Export::stash_hypervolume(const double hv) {
    hypervolume.push_back(hv);
}

void Export::export_data(const std::chrono::microseconds time, const int runs, const export_type type, const Problem *problem,
    const int population_size, const int generation_max, const double crossover_alpha, const double mutation_distribution,
    const double mutation_probability, const int seed,const std::vector<double>& Objective_space,const std::string& directory) {
    export_results(problem,population_size,runs,Objective_space,directory);
    export_meta(time,runs,problem,population_size,generation_max,crossover_alpha,mutation_distribution,mutation_probability,
        seed,directory);
    export_hypervolume(runs,directory);
}
#endif
