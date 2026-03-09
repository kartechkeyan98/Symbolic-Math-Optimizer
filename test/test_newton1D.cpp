#include<cstdio>
#include<cmath>
#include<functional>

#include<utils/random.hpp>
#include<optimization/line_searches.hpp>

#include<symbolic.hpp>
using namespace symbolic;


int main(void){
    // init randomness
    random_generator rg;
    double e= 1e-7;
    using func1d= std::function<double(double)>;

    expr x= variable("x");
    expr f0= (x^4) - x + 1;
    expr f1= f0->diff("x");
    expr f2= f1->diff("x");
    
    func1d f=  [f0, x](double val)->double{
        env vars;
        std::string varname= x->toString();
        vars[varname]=val;
        return f0->evaluate(vars);
    };
    func1d df= [f1, x](double val)->double{ 
        env vars;
        std::string varname= x->toString();
        vars[varname]=val;
        return f1->evaluate(vars);
    };
    func1d d2f=[f2, x](double val)->double{
        env vars;
        std::string varname= x->toString();
        vars[varname]=val;
        return f2->evaluate(vars);
    };

    std::cout<<x->toString()<<std::endl;
    std::cout<<f0->toString()<<std::endl;
    std::cout<<f1->toString()<<std::endl;
    std::cout<<f2->toString()<<std::endl;

    double x_min= newton_search(f, df, d2f, rg);
    return 0;
}