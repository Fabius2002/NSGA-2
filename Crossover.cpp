#include "Crossover.hpp"

#include <algorithm>


void blend_crossover(
    const int parent_x,const int parent_y,const double alpha,std::vector<double> &data,const Problem* problem,const int index,std::mt19937_64& mt) {
    const int dim=problem->get_Decision_space_dim();
    for (int i=0;i<dim;i++) {
        const double min=std::min(data[parent_x*dim+i],data[parent_y*dim+i]);
        const double max=std::max(data[parent_x*dim+i],data[parent_y*dim+i]);
        const double distance=max-min;
        const double low=min-alpha*distance;
        const double up=max+alpha*distance;
        const double max_bound=problem->get_Decision_boundaries()[i][1];
        const double min_bound=problem->get_Decision_boundaries()[i][0];
        std::uniform_real_distribution<double> dist(low,up);
        data[index*dim+i]=std::clamp(dist(mt),min_bound,max_bound);
        data[index*dim+i+dim]=std::clamp(dist(mt),min_bound,max_bound);
    }
}
