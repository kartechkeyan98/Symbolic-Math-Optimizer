#include<cstdio>
#include<cmath>
#include<functional>

#include<utils/random.hpp>
#include<optimization/section_searches.hpp>

#include<symbolic.hpp>

using namespace std;

int main(void){
    // init randomness
    random_generator rg;

    symbolic::expr x= symbolic::variable("x");
    symbolic::expr f= (x^4) + 2*((2*x-1)^2);
    symbolic::expr df= f->diff("x");

    // define your unimodal function and search bracket
    std::function<double(double)> f0= [f,x](double val)->double{
        symbolic::env vars;
        vars[x->toString()]= val;
        return f->evaluate(vars);
    };  
    std::function<double(double)> f1= [df, x](double val)->double{
        symbolic::env vars;
        vars[x->toString()]= val;
        return df->evaluate(vars);
    };
    double a= -5, b= 5;

    section_search(f0, a,b, rg);
    golden_section_search(f0, a,b);
    fibonacci_search(f0, a,b, 1e-8);
    bisection_search(f0, f1, a, b);

    return 0;
}