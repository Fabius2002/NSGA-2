#include "Help.hpp"
#include <vector>
#include  <algorithm>
std::vector<std::vector<int>> fast_non_dominated_sort(const std::vector<double> &objective_space,std::vector<int> &rank,const int population_size,const Problem* problem){
    auto Dominated_points = std::vector<std::vector<int>>(population_size);
    auto Domination_count = std::vector<int>(population_size);
    auto fronts = std::vector<std::vector<int>>(1);
    for (int p = 0; p < population_size; p++)
    {

        for (int q = 0; q < population_size; q++)
        {
            if (dominates(p,q,objective_space,problem) == 1) {
                Dominated_points[p].push_back(q);
            }
            else if (dominates(p,q,objective_space,problem) == 0) {
                Domination_count[p]++;
            }
        }
        if (Domination_count[p]==0) {
            rank[p]=1;
            fronts[0].push_back(p);
        }
    }

    int i=1;
    while (!fronts[i-1].empty()) {
        auto front=std::vector<int>();
        for (const int p : fronts[i-1]) {
            for (int q : Dominated_points[p]) {
                Domination_count[q]--;
                if (Domination_count[q] == 0) {
                    rank[q] = i + 1;
                    front.push_back(q);
                }
            }
        }
        i++;
        fronts.push_back(front);
    }
    fronts.pop_back();
    return fronts;
}




int dominates(const int x,const int y,const std::vector<double> &objective_space,const Problem* problem){
    bool dominates_check = false;
    bool dominated_check = false;
    const int index_x=x*problem->get_Objective_space_dim();
    const int index_y=y*problem->get_Objective_space_dim();
    for(int objective=0;objective<problem->get_Objective_space_dim();objective++){
        if(objective_space[index_x+objective]<objective_space[index_y+objective]){
            dominates_check = true;
        }
        if(objective_space[index_x+objective]>objective_space[index_y+objective]){
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

std::vector<int> sort_after_obj(const std::vector<double>& objective_space, const int objective,
    const int objective_dim,const int population_size,const std::vector<int>& front) {
    std::vector<std::tuple<double,int>> obj_and_ind;
    obj_and_ind.reserve(front.size());
    for (int i : front) {
        obj_and_ind.emplace_back(objective_space[i*objective_dim+objective],i);
    }
    std::ranges::sort(obj_and_ind);
    std::vector<int> sorted_indices;
    sorted_indices.reserve(population_size);
    for (const auto& tuple : obj_and_ind) {
        sorted_indices.push_back(std::get<1>(tuple));
    }
    return sorted_indices;
}

std::vector<int> sort_after_crowding_distance(const std::vector<double>& crowding_distance,const std::vector<int>& front) {
    std::vector<std::tuple<double,int>> crowding_and_ind;
    crowding_and_ind.reserve(front.size());
    for (int i : front) {
        crowding_and_ind.emplace_back(crowding_distance[i],i);
    }
    std::ranges::sort(crowding_and_ind, std::greater{});
    std::vector<int> sorted_indices;
    sorted_indices.reserve(crowding_and_ind.size());
    for (const auto& tuple : crowding_and_ind) {
        sorted_indices.push_back(std::get<1>(tuple));
    }
    return sorted_indices;
}