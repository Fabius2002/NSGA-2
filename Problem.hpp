#ifndef PROBLEM_H
#define PROBLEM_H
#include <cmath>

struct Problem {
    virtual int get_Decision_space_dim() const =0;
    virtual int get_Objective_space_dim()const =0;
    virtual void evaluate(double* input, int population_size, double* result) const = 0;
    virtual ~Problem() = default;
};

struct SCH1:Problem{
    static constexpr int Decision_space_dim=1;
    static constexpr int Objective_space_dim=2;
    float Decision_boundaries[Decision_space_dim][2]={{-3.0,3.0}};

    static double Objective_fun_1(double x){
        return pow(x,2);
    }
    static double Objective_fun_2(double x){
        return pow((x-2),2);
    }
    void evaluate(double* input, int population_size, double* result) const override{
        for(int i=0;i<population_size;i++){
            result[i*Objective_space_dim+0]=Objective_fun_1(input[i]);
            result[i*Objective_space_dim+1]=Objective_fun_2(input[i]);
        }
    };
};


#endif //PROBLEM_H
