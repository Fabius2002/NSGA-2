#include "NSGA.hpp"

#include <algorithm>
#include <limits>
#include <fstream>
#include "Crossover.hpp"
#include "Help.hpp"
#include "Mutator.hpp"

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
//TODO: maybe make sure that you cannot divide by zero if i choose to
//TODO: make it so it
void NSGA::crowding_distance_calculation(const std::vector<int>& front) {
    auto front_values=std::vector<double>(front.size());//for front specific
    for (const int i : front) {//for front specific
        crowding_distance[i]=0.0;//for front specific
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

void NSGA::generate_offspring_population(const double alpha,const double distribution) {
    for (int index=population_size;index<population_size*2;index=index+2) {
        const int parent_x=binary_tournament_selection();
        const int parent_y=binary_tournament_selection();
        blend_crossover(parent_x,parent_y,alpha,Decision_space,problem,index,mt);
        polynomial_mutation(Decision_space,distribution,problem,index,mt);
        polynomial_mutation(Decision_space,distribution,problem,index+1,mt);
    }
}
void NSGA::run(const int generation_max) {
    const int max_dim=problem->get_Decision_space_dim();
    init_population();
    problem->evaluate(Decision_space,population_size,Objective_space,0);
    fast_non_dominated_sort(Objective_space,rank,population_size,problem);
    generate_offspring_population(0.5,20);//make this changeable, IDK how yet
    int gen=1;
    while (gen<generation_max) {
        problem->evaluate(Decision_space,population_size,Objective_space,population_size);
        auto fronts=fast_non_dominated_sort(Objective_space,rank,population_size*2,problem);
        std::vector<double> new_generation;
        new_generation.reserve(population_size*max_dim*2);
        int i=0;
        int added_elements=0;
        while (added_elements<population_size) {
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
        }Decision_space=new_generation;
        Decision_space.resize(population_size*2*problem->get_Decision_space_dim());
        generate_offspring_population(0.5,20.0);
        gen=gen+1;
    }

}

void NSGA::export_data() {
    std::ofstream output("nsga_results.csv");
    for (int dim=0;dim<problem->get_Decision_space_dim();dim++) {
        output <<"x";
    }
    output << std::endl;
    for (int i=0;i<population_size;i++) {
        for (int dim=1;dim<=problem->get_Decision_space_dim();dim++) {
            output << Decision_space[i*dim] << " ,";
        }
        output << std::endl;
    }
    output.close();
}
