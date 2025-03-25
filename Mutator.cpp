#include "Mutator.hpp"
#include <cstdlib>
#include <algorithm>
void polynomial_mutation(std::vector<double>& data,const int index, const double mutation_distribution,
                         const double mutation_probability,const Problem* problem,std::mt19937_64& mt) {
    std::uniform_real_distribution<double> dist(0,1);
    const int Decision_space_dimensions=problem->get_Decision_space_dim();
    for (int dim=0;dim<Decision_space_dimensions;dim++) {
        if (dist(mt)>mutation_probability) {
        continue;
    }
        const double max=problem->get_Decision_boundaries()[dim][1];
        const double min=problem->get_Decision_boundaries()[dim][0];
        const double range=max-min;
        double delta;
        const int data_index=index*Decision_space_dimensions+dim;
        if (const double r=dist(mt); r<=0.5) {
            const double delta_part=(data[data_index]-min)/(range);
            delta=std::pow(2*r+(1-2*r)*std::pow(1-delta_part,mutation_distribution+1),1/(mutation_distribution+1))-1;
        }
        else {
            const double delta_part=(max-data[data_index])/(range);
            delta=1-std::pow(2*(1-r) + 2*(r-0.5)*std::pow(1-delta_part,mutation_distribution+1),1/(mutation_distribution+1));
        }
        data[data_index]=std::clamp(data[data_index]+delta*range,min,max);
    }

}
