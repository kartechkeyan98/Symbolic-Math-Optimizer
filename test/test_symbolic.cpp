#include<iostream>

#include<symbolic/expression.hpp>
#include<symbolic/leafs.hpp>
#include<symbolic/math.hpp>
#include<symbolic/trig.hpp>
#include<symbolic/visuals.hpp>

using namespace symbolic;

int main(void){
    expr x= variable("x");
    expr y= variable("y");

    env vars;
    vars["x"] = 8.0;
    vars["y"] = 2.0;
    std::cout<<x->toString()<<" = "<<x->evaluate(vars)<<std::endl;
    std::cout<<y->toString()<<" = "<<y->evaluate(vars)<<std::endl;
    
    expr f= sqrt(x*x + y*y);
    std::cout<<"f = "<<f->toString()<<" = "<<f->evaluate(vars)<<std::endl;
    export_to_dot(f, "./dots/fig1.dot");

    expr d= f->diff("x");
    std::cout<<"d = df/dx = "<<d->toString()<<" = "<<d->evaluate(vars)<<std::endl;
    export_to_dot(d, "./dots/fig2.dot");
}