#ifndef MUTATOR_HPP
#define MUTATOR_HPP
#include <vector>
#include <random>

#include "Problem.hpp"

void polynomial_mutation(std::vector<double>& data, double distribution,const Problem* problem,int index,std::mt19937_64& mt);
#endif //MUTATOR_HPP
