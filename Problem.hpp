#ifndef PROBLEM_H
#define PROBLEM_H
#include <cmath>
#include <vector>

struct Problem {
    [[nodiscard]] virtual int get_Decision_space_dim() const =0;
    [[nodiscard]] virtual int get_Objective_space_dim()const =0;
    [[nodiscard]] virtual std::vector<std::vector<double>> get_Decision_boundaries()const =0;
    virtual void evaluate(const std::vector<double>& input,int population_size, std::vector<double>& result,int offset) const = 0;
    virtual ~Problem() = default;
};

struct SCH1 final :Problem{
    static constexpr int Decision_space_dim=1;
    static constexpr int Objective_space_dim=2;
    const std::vector<std::vector<double>> Decision_boundaries={{-3.0,3.0}};

    static double Objective_fun_1(double x){
        return pow(x,2);
    }
    static double Objective_fun_2(double x){
        return pow((x-2),2);
    }
    void evaluate(const std::vector<double>& input, const int population_size, std::vector<double>& result,const int offset) const override{
        for(int i=0;i<population_size;i++){
            result[(i+offset)*Objective_space_dim+0]=Objective_fun_1(input[i+offset]);
            result[(i+offset)*Objective_space_dim+1]=Objective_fun_2(input[i+offset]);
        }
    };
    [[nodiscard]] int get_Decision_space_dim() const override{return Decision_space_dim;}
    [[nodiscard]] int get_Objective_space_dim() const override{return Objective_space_dim;}
    [[nodiscard]] std::vector<std::vector<double>> get_Decision_boundaries() const override {
        return Decision_boundaries;
    }
};


#endif //PROBLEM_H
