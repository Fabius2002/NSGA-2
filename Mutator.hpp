#ifndef MUTATOR_HPP
#define MUTATOR_HPP
#include <vector>
#include <random>

#include "Problem.hpp"
//uses standard polynomial mutation as can be seen in Carles-Bou, J.L., Galán, S.F. Self-adaptive polynomial mutation in NSGA-II. Soft Comput 27,
//17711–17727 (2023). https://doi.org/10.1007/s00500-023-09049-0.
//Takes a given Index and mutates the gene in the data vector at the given index. The mutation distribution picks decides the range in which a gene is mutated,
//meaning larger values narrow down the potential mutation area and lower values enlarge the possible area.
//The mutation_probability is the probability with which a given gene is mutated.
void polynomial_mutation(std::vector<double>& data,int index,double mutation_distribution,
double mutation_probability,const Problem* problem,std::mt19937_64& mt);
#endif //MUTATOR_HPP
