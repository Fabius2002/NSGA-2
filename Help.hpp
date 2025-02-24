#ifndef HELP_HPP
#define HELP_HPP
#include "Problem.hpp"

void fast_non_dominated_sort();
int dominates(const double* x,const double* y,const Problem* problem);
#endif //HELP_HPP
