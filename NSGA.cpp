#include "NSGA.hpp"

#include <algorithm>
#include <limits>
#include <fstream>
#include <iostream>

#include "Crossover.hpp"
#include "Export.hpp"
#include "Help.hpp"
#include "Mutator.hpp"

#if DEBUG
#include "Debug.hpp"
#endif

void NSGA::init_population() {
    const auto boundaries=problem->get_Decision_boundaries();
    std::vector<std::uniform_real_distribution<double>> distributions;
    for (int dim=0;dim<problem->get_Decision_space_dim();dim++) {
        distributions.emplace_back(boundaries[dim][0], boundaries[dim][1]);
    }
    for (int i=0;i<population_size;i++) {
        for (int dim=0;dim<problem->get_Decision_space_dim();dim++) {
            Decision_space[INDEX(i,problem->get_Decision_space_dim())+dim]=distributions[dim](mt);

        }
    }
}
void NSGA::crowding_distance_calculation(const std::vector<int>& front) {
    auto front_values=std::vector<double>(front.size());
    for (const int i : front) {
        crowding_distance[i]=0.0;
    }
    for (int obj=0;obj<problem->get_Objective_space_dim();obj++) {
        std::vector<int> sorted_index=sort_after_obj(Objective_space,obj,problem->get_Objective_space_dim(),population_size,front);
        crowding_distance[sorted_index[0]]=crowding_distance[sorted_index.back()]=std::numeric_limits<double>::infinity();
        const double normalization=Objective_space[INDEX(sorted_index.back(),problem->get_Objective_space_dim())+obj]-
            Objective_space[INDEX(sorted_index[0],problem->get_Objective_space_dim())+obj];
        for (int i=1;i<sorted_index.size()-1;i++) {
            crowding_distance[sorted_index[i]]+=(Objective_space[INDEX(sorted_index[i+1],problem->get_Objective_space_dim())+obj]-
                Objective_space[INDEX(sorted_index[i-1],problem->get_Objective_space_dim())+obj])/normalization;
        }
    }
}
int NSGA::binary_tournament_selection(){
    std::uniform_int_distribution<int> dist(0,population_size-1);
    const int parent_x=dist(mt);
    const int parent_y=dist(mt);
    if (rank[parent_x]<rank[parent_y]) return parent_x;
    if (rank[parent_x]>rank[parent_y]) return parent_y;
    if (crowding_distance[parent_x]>crowding_distance[parent_y]) return parent_x;
    if (crowding_distance[parent_x]<crowding_distance[parent_y]) return parent_y;
    std::uniform_int_distribution<int> dist2(0, 1);
    return dist2(mt)==1 ? parent_x : parent_y;
}

void NSGA::generate_offspring_population(const double alpha,const double mutation_distribution, const double mutation_probability,const bool uneven_count) {
    for (int index=population_size;index<population_size*2;index=index+2) {
        const int parent_x=binary_tournament_selection();
        const int parent_y=binary_tournament_selection();
        blend_crossover(parent_x,parent_y,alpha,Decision_space,problem,index,mt,uneven_count,population_size);
        polynomial_mutation(Decision_space,index,mutation_distribution,mutation_probability,problem,mt);
        if (uneven_count) {
            if (!index+1==population_size)
        polynomial_mutation(Decision_space,index+1,mutation_distribution,mutation_probability,problem,mt);
        }
    }
}
#if EXPORT
double NSGA::run(Export * exporter,const int run_number) {
#else
double NSGA::run(const int run_number) {
#endif
    double hypervolume=0;
    const int max_dim=problem->get_Decision_space_dim();
    const bool uneven_count=(population_size%2==1);
    init_population();
    problem->evaluate(Decision_space,population_size,Objective_space,0);
    const auto fronts=fast_non_dominated_sort(Objective_space,rank,population_size,problem);
    generate_offspring_population(crossover_alpha, mutation_distribution,mutation_probability,uneven_count);
    int gen=1;
    if (!gen<generation_max)
        hypervolume=calculate_hypervolume_2d(fronts[0]);
#if EXPORT
    exporter->stash_hypervolume(calculate_hypervolume_2d(fronts[0]));
#endif

#if DEBUG
    Debug::debug_init(gen,generation_max,calculate_hypervolume_2d(fronts[0]),fronts[0].size(),population_size);
#endif

    while (gen<generation_max) {
        problem->evaluate(Decision_space,population_size,Objective_space,population_size);
        auto fronts=fast_non_dominated_sort(Objective_space,rank,population_size*2,problem);
        std::vector<double> new_generation;
        new_generation.reserve(population_size*max_dim*2);
        int i=0;
        int added_elements=0;
        while (added_elements+fronts[i].size()<=population_size) {
                crowding_distance_calculation(fronts[i]);
            for (const int index:fronts[i]) {
                for (int dim=0;dim<problem->get_Decision_space_dim();dim++) {
                    new_generation.push_back(Decision_space[index*problem->get_Decision_space_dim()+dim]);
                }
            }
            added_elements=added_elements+fronts[i].size();
            i=i+1;
        }
        crowding_distance_calculation(fronts[i]);
        const auto sorted_front=sort_after_crowding_distance(crowding_distance,fronts[i]);
        int front_index=0;
        while (added_elements<population_size) {
            for (int dim=0;dim<problem->get_Decision_space_dim();dim++) {
                new_generation.push_back(Decision_space[sorted_front[front_index]*problem->get_Decision_space_dim()+dim]);
            }
            front_index=front_index+1;
            added_elements=added_elements+1;
        }
        Decision_space=new_generation;
        problem->evaluate(Decision_space,population_size,Objective_space,0);

#if EXPORT
        exporter->stash_hypervolume(calculate_hypervolume_2d(fronts[0]));
#endif
#if DEBUG
Debug::debug_gen(gen,generation_max,calculate_hypervolume_2d(fronts[0]),fronts[0].size(),population_size);
#endif
        Decision_space.resize(population_size*2*problem->get_Decision_space_dim());
        generate_offspring_population(crossover_alpha,mutation_distribution,mutation_probability, uneven_count);
        gen=gen+1;
        if (!gen<generation_max)
            hypervolume=calculate_hypervolume_2d(fronts[0]);
    }
#if DEBUG
    Debug::debug_final(run_number,problem,generation_max,population_size,mutation_distribution,mutation_probability,crossover_alpha);
#endif
    return hypervolume;
}




double NSGA::calculate_hypervolume_2d(const std::vector<int>& front) const {
    std::vector<std::vector<double>> sort;
    for (int i : front) {
        sort.push_back({Objective_space[i*2],Objective_space[i*2+1]});
    }
    std::ranges::sort(sort);
    const std::vector<double> ref=problem->get_reference_point();
    double hypervolume=0;
    for (int i=0;i<sort.size()-1;i++) {
        hypervolume=hypervolume+(sort[i+1][0]-sort[i][0])*(ref[1]-sort[i][1]);
    }
    return hypervolume+(ref[0]-sort.back()[0])*(ref[1]-sort.back()[1]);
}