#include "Help.hpp"
#include <vector>
#define INDEX(i, dim) ((i) * (dim))
void fast_non_dominated_sort(const double* objective_space,int* rank,const int population_size,const Problem* problem){
    std::vector<std::vector<int>> Dominated_points = std::vector<std::vector<int>>();
    int* Domination_count = new int[population_size]();
    for (int p = 0; p < population_size; p++)
    {
        for (int q = 0; q < population_size; q++)
        {
            if (dominates(&objective_space[p*problem->get_Objective_space_dim()],
                &objective_space[INDEX(q,problem->get_Objective_space_dim())],problem) == 1) {
                Dominated_points[p].push_back(q);
            }
            else if (dominates(&objective_space[p*problem->get_Objective_space_dim()],
                &objective_space[INDEX(q,problem->get_Objective_space_dim())],problem) == 0) {
                Domination_count[p]++;
            }
        }
    }
}




int dominates(const double* x,const double* y,const Problem* problem){
    bool dominates_check = false;
    bool dominated_check = false;
    for(int objectives=0;objectives<problem->get_Objective_space_dim();objectives++){
        if(x[objectives]>y[objectives]){
            dominates_check = true;
        }
        if(x[objectives]<y[objectives]){
            dominated_check = true;
        }
        if(dominates_check && dominated_check){
            return -1;
        }
    }
    if(dominates_check){return 1;}
    if(dominated_check){return 0;}
    return -1;
}

