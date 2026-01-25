#include<cstdio>
#include<cmath>
#include<functional>

#include<random.hpp>
#include<section_searches.hpp>

using namespace std;

int main(void){
    // init randomness
    random_generator rg;

    // define your unimodal function and search bracket
    std::function<double(double)> f= [](double x)->double{
        return pow(x,4) + 2*pow(2*x - 1, 2);
    };  
    std::function<double(double)> df= [f](double x)->double{
        return (f(x+1e-5) - f(x))/1e-5;
    };
    double a= -5, b= 5;

    section_search(f, a,b, rg);
    golden_section_search(f, a,b);
    fibonacci_search(f, a,b, 1e-8);
    bisection_search(f, df, a, b);

    return 0;
}