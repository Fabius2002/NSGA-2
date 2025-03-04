#ifndef HELP_HPP
#define HELP_HPP
#include "Problem.hpp"
#define INDEX(i, dim) ((i) * (dim))

std::vector<std::vector<int>> fast_non_dominated_sort(const std::vector<double> &objective_space,std::vector<int> &rank,int population_size,const Problem* problem);
int dominates(int x,int y,const std::vector<double> &objective_space,const Problem* problem);
std::vector<int> sort_after_obj(const std::vector<double>& objective_space,int objective,int objective_dim,int population_size,const std::vector<int>& front);
std::vector<int> sort_after_crowding_distance(const std::vector<double>& crowding_distance,const std::vector<int>& front);
#endif //HELP_HPP
