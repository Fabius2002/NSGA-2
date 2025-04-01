#include "Crossover.hpp"

#include <algorithm>

//simple blend crossover that takes an index and fills the next two points with blend crossover. The alpha parameter balances exploration with exploitation.
//A smaller alpha value leads to a more narrow selection, while a bigger value leads to a larger selection area
void blend_crossover(
    const int parent_x,const int parent_y,const double alpha,std::vector<double> &data,const Problem* problem,const int index,std::mt19937_64& mt,
    const bool uneven_count,const int population_size) {
    const int dim=problem->get_Decision_space_dim();
    for (int i=0;i<dim;i++) {
        const double min=std::min(data[parent_x*dim+i],data[parent_y*dim+i]);
        const double max=std::max(data[parent_x*dim+i],data[parent_y*dim+i]);
        const double distance=max-min;
        const double max_bound=problem->get_Decision_boundaries()[i][1];
        const double min_bound=problem->get_Decision_boundaries()[i][0];
        std::uniform_real_distribution<double> dist(min-alpha*distance,max+alpha*distance);
        data[index*dim+i]=std::clamp(dist(mt),min_bound,max_bound);
        if (uneven_count) {
            if (!index+1==population_size)
            data[index*dim+i+dim]=std::clamp(dist(mt),min_bound,max_bound);
        }
    }
}
