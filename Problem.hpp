#ifndef PROBLEM_H
#define PROBLEM_H
#include <cmath>
#include <vector>


#if DEBUG||EXPORT
#include <fstream>
#endif


struct Problem {
    [[nodiscard]] virtual int get_Decision_space_dim() const =0;
    [[nodiscard]] virtual int get_Objective_space_dim()const =0;
    [[nodiscard]] virtual std::vector<double> get_reference_point() const=0;
    [[nodiscard]] virtual std::vector<std::vector<double>> get_Decision_boundaries()const =0;
    virtual void evaluate(const std::vector<double>& input,int population_size, std::vector<double>& result,int offset) const = 0;
    virtual ~Problem() = default;

#if DEBUG||EXPORT
#define output_prob() debug_output_prob()
    [[nodiscard]] virtual std::string debug_output_prob() const =0;
#else
#define output_prob()
#endif
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
    [[nodiscard]] std::vector<double> get_reference_point() const override{return{9.1,25.1};}

#if DEBUG||EXPORT
    [[nodiscard]] std::string debug_output_prob() const override{
        return "SCH1";
    }
#endif
};


struct ZDT3 final :Problem {
    static constexpr int Decision_space_dim=30;
    static constexpr int Objective_space_dim=2;
    const std::vector<std::vector<double>> Decision_boundaries=std::vector(30, std::vector<double>{0.0, 1.0});

    static double Objective_fun_1(double x){
        return x;
    }
    static double Objective_fun_2_helper(const std::vector<double>& input,const int index){
        double sum=0;
        for (int i=1;i<Decision_space_dim;i++) {
            sum=sum+input[index*Decision_space_dim+i];
        }
        return 1.0+ 9.0/(29.0)*sum;
    }
    static double Objective_fun_2(const std::vector<double>& input,const int index){
        const double g=Objective_fun_2_helper(input,index);
        const double f=Objective_fun_1(input[index*Decision_space_dim]);
        return g*(1.0 - sqrt(f/g) - (f/g) * std::sin(10*M_PI*f));
    }
    [[nodiscard]] int get_Decision_space_dim() const override{return Decision_space_dim;}
    [[nodiscard]] int get_Objective_space_dim() const override{return Objective_space_dim;}
    [[nodiscard]] std::vector<std::vector<double>> get_Decision_boundaries() const override {
        return Decision_boundaries;
    }
    [[nodiscard]] std::vector<double> get_reference_point() const override{return{1.1,11.1};}
    void evaluate(const std::vector<double>& input, const int population_size, std::vector<double>& result,const int offset) const override{
        for(int i=0;i<population_size;i++){
            result[(i+offset)*Objective_space_dim+0]=Objective_fun_1(input[i*Decision_space_dim+offset*Decision_space_dim]);
            result[(i+offset)*Objective_space_dim+1]=Objective_fun_2(input,i+offset);
        }
    };

#if DEBUG||EXPORT
    [[nodiscard]] std::string debug_output_prob() const override {
        return "ZDT3";
    }
#endif
};


struct ZDT2 final :Problem {
    static constexpr int Decision_space_dim=30;
    static constexpr int Objective_space_dim=2;
    const std::vector<std::vector<double>> Decision_boundaries=std::vector(30, std::vector<double>{0.0, 1.0});

    static double Objective_fun_1(double x){
        return x;
    }
    static double Objective_fun_2_helper(const std::vector<double>& input,const int index){
        double sum=0;
        for (int i=1;i<Decision_space_dim;i++) {
            sum=sum+input[index*Decision_space_dim+i];
        }
        return 1.0+ 9.0/(29.0)*sum;
    }
    static double Objective_fun_2(const std::vector<double>& input,const int index){
        const double g=Objective_fun_2_helper(input,index);
        const double f=Objective_fun_1(input[index*Decision_space_dim]);
        return 1-(f/g)*(f/g);
    }
    [[nodiscard]] int get_Decision_space_dim() const override{return Decision_space_dim;}
    [[nodiscard]] int get_Objective_space_dim() const override{return Objective_space_dim;}
    [[nodiscard]] std::vector<std::vector<double>> get_Decision_boundaries() const override {
        return Decision_boundaries;
    }
    [[nodiscard]] std::vector<double> get_reference_point() const override{return{1.1,1.1};}
    void evaluate(const std::vector<double>& input, const int population_size, std::vector<double>& result,const int offset) const override{
        for(int i=0;i<population_size;i++){
            result[(i+offset)*Objective_space_dim+0]=Objective_fun_1(input[i*Decision_space_dim+offset*Decision_space_dim]);
            result[(i+offset)*Objective_space_dim+1]=Objective_fun_2(input,i+offset);
        }
    }

#if DEBUG||EXPORT
    [[nodiscard]] std::string debug_output_prob() const override {
        return "ZDT2";
    }
#endif
};
#endif //PROBLEM_H
