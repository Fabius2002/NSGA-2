#ifndef CROSSOVER_HPP
#define CROSSOVER_HPP
#include <vector>
#include <random>
#include"Problem.hpp"
#endif //CROSSOVER_HPP
void blend_crossover(int parent_x,int parent_y,double alpha,
    std::vector<double> &data,const Problem* problem,int index,std::mt19937_64& mt,bool uneven_count,int population_size);