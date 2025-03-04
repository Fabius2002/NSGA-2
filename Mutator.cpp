#include "Mutator.hpp"

#include <cstdlib>
#include <algorithm>


void polynomial_mutation(std::vector<double>& data, const double distribution,const Problem* problem,const int index,std::mt19937_64& mt) {
    double perturbation_factor;
    const int Decision_space_dimensions=problem->get_Decision_space_dim();
    std::uniform_real_distribution<double> dist(0,1);
    for (int dim=0;dim<Decision_space_dimensions;dim++) {
        const double max=problem->get_Decision_boundaries()[dim][1];
        const double min=problem->get_Decision_boundaries()[dim][0];
        const double perturbation=max-min;
        if (const double r=dist(mt); r<0.5) {
            perturbation_factor=std::pow((2*r),(1/(distribution+1)))-1;
        }
        else {
            perturbation_factor=1-std::pow((2*(1-r)),(1/(distribution+1)));
        }
        data[index*Decision_space_dimensions+dim]=std::clamp((data[index*Decision_space_dimensions+dim]+perturbation_factor*perturbation),min,max);
    }


}
