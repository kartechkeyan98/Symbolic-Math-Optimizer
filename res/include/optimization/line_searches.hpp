#pragma once

#include<functional>

#include<utils/random.hpp>

using func1d= std::function<double(double)>;

/**
 * @param f the function under consideration, to be minimized
 * @param df the first derivitive of f
 * @param d2f the second derivitive of f
 * @param e tolerance by default 1e-5
 */
double newton_search(
    const func1d& f,
    const func1d& df,
    const func1d& d2f,
    random_generator& rg,
    double e= 1e-5,
    int iter_limit= 1000 
){
    // choose any random starting point
    double x = rg.uniform_random_double(-5, 5);
    double x1= x - df(x)/d2f(x);

    int c= 0;
    while(fabs(x1 - x) > e && c < 1000){
        double t= x1 - df(x1)/d2f(x1);
        x= x1, x1= t;
        c++;
    }

    printf("No.of Iterations of [newton_search(...)]: %d\n",c);
    printf("The minimum occurs at: [%0.5f]\n", (x+x1)/2);
    printf("The minimum value is: [%0.5f]\n\n", f((x+x1)/2));
    return (x + x1)/2;
}