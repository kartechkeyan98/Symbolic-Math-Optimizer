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
    vars["y"] = 5.6;
    std::cout<<x->toString()<<" = "<<x->evaluate(vars)<<std::endl;
    std::cout<<y->toString()<<" = "<<y->evaluate(vars)<<std::endl;

    // Basic Stuff
    expr z= x + y;
    expr w= x * y;
    expr f= x - y;
    expr g= x / y;
    std::cout<<z->toString()<<" = "<<z->evaluate(vars)<<std::endl;
    std::cout<<w->toString()<<" = "<<w->evaluate(vars)<<std::endl;
    std::cout<<f->toString()<<" = "<<f->evaluate(vars)<<std::endl;
    std::cout<<g->toString()<<" = "<<g->evaluate(vars)<<std::endl;

    expr r= sin(z*w + f/g);

    // Visualize
    export_to_dot(r, "./dots/fig1.dot");
}