#ifndef NSGA_H
#define NSGA_H
#include "Problem.hpp"
struct NSGA {
    double* Decision_space;
    double* Objective_space;
    int population_size;
    Problem* problem;
    double* crowding_distance;
    int* rank;
    NSGA(Problem* problem,int population_size) {
        this->problem=problem;
        this->population_size=population_size;
        Decision_space=new double[population_size*problem->get_Decision_space_dim()];
        Objective_space=new double[population_size*problem->get_Objective_space_dim()];
        crowding_distance=new double[population_size];
        rank=new int[population_size];
    };
    ~NSGA() {
        delete[] Decision_space;
        delete[] Objective_space;
        delete[] crowding_distance;
        delete[] rank;
    }
    void run();
    void print_result();
    void init_population();
    void crowding_distance_calculation();
    void tournament_selection();
    void crossover();
    void mutation();

};
#endif
