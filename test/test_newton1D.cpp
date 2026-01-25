#include<cstdio>
#include<cmath>
#include<functional>

#include<random.hpp>
#include<line_searches.hpp>


int main(void){
    // init randomness
    random_generator rg;
    double e= 1e-7;
    using func1d= std::function<double(double)>;

    func1d f=  [](double x)->double{
        return pow(x,4) + 2*pow(2*x - 1, 2);
    };
    func1d df= [f, e](double x)->double{ 
        return (f(x+e) - f(x-e))/(2*e);
    };
    func1d d2f=[f, e](double x)->double{
        return (f(x + e) + f(x - e) - 2*f(x))/(e*e);
    };

    double x_min= newton_search(f, df, d2f, rg);
    return 0;
}