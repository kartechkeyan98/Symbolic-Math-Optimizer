#pragma once

#include<cstdio>
#include<functional>
#include<cmath>
#include<stdexcept>

#include<utils/random.hpp>
#include<utils/fibonacci.hpp>

/**
 * @param f is a std::function that contains the univariate function
 * @param a,b are the initial search bracket end points, ie we search for min in [a,b]
 * @param rg is the random number generator that will be defined in the main function (usually)
 * @param e is the tolerance parameter, default value is 10^-5
 * @param iter_limit to limit no.of iterations
 * @brief does general section based search assuming that f is unimodal.
 */
double section_search(
    const std::function<double(double)>& f, 
    double a, double b, 
    random_generator& rg, 
    double e= 1e-5,
    int iter_limit= 1000 
){
    int c= 0;
    double a0= a, b0= b;
    while(b-a > e && c < iter_limit){
        double ad= rg.uniform_random_double(a,b);
        double bd= rg.uniform_random_double(ad,b);

        double fad= f(ad);
        double fbd= f(bd);

        if(fad <= fbd){
            b= bd;
        }
        else{
            a= ad;
        }
        c++;
    }
    printf("No.of Iterations of [section_search(.., %0.2f, %0.2f, ...)]: %d\n", a0,b0,c);
    printf("The minimum occurs at: [%0.5f]\n", (a+b)/2);
    printf("The minimum value is: [%0.5f]\n\n", f((a+b)/2));
    return (a+b)/2;   
}

/**
 * @param f is a std::function that contains the univariate function
 * @param a,b are the initial search bracket end points, ie we search for min in [a,b]
 * @param rg is the random number generator that will be defined in the main function (usually)
 * @param e is the tolerance parameter, default value is 10^-5
 * @param iter_limit is the limit on no.of iterations so that things don't get messed up
 * @brief does golden section based search assuming that f is unimodal.
 */
double golden_section_search(
    const std::function<double(double)>& f, 
    double a, double b,  
    double e= 1e-5, 
    int iter_limit= 1000
){
    if(a > b) throw std::runtime_error("Provide proper interval [a,b] where a <= b\n");

    double rho= (3-std::sqrt(5))/2;
    double a0= a, b0= b;

    double L= b-a;
    double ad= a + rho*L, bd= b - rho*L;
    double fad= f(ad), fbd= f(bd);

    int c=0;
    while(b - a > e && c < iter_limit){
        if(fad <= fbd){
            b= bd;      // set new interval to [a, bd]
            bd= ad;     // reuse ad as the new right interior (new bd)
            fbd= fad;   // reuse function value
            
            L= b-a;
            ad= a + rho*L;
            fad= f(ad);
        }
        else{
            a= ad;      // set new interval to [ad, b]
            ad= bd;     // reuse bd as new ad
            fad= fbd;   // reuse function value

            L= b-a;
            bd= b - rho*L;
            fbd= f(bd);
        }
        c++;
    }

    printf("No.of iteration of golden_section_search(..., %0.2f, %0.2f, ...) = %d\n", a0, b0, c);
    printf("The minimum occurs at: [%0.5f]\n", (a+b)/2);
    printf("The minimum value is: [%0.5f]\n\n", f((a+b)/2));

    return (a+b)/2;
}


/**
 * @param f is a std::function that contains the univariate function
 * @param a,b are the initial search bracket end points, ie we search for min in [a,b]
 * @param e is the tolerance parameter, default value is 10^-5
 * @brief does fibonacci search assuming that f is unimodal.
 */
double fibonacci_search(
    const std::function<double(double)>& f, 
    double a, double b,  
    double e= 1e-5
){
    if(a > b) throw std::runtime_error("Provide proper interval [a,b] where a <= b\n");

    // generate fibonacci no.s till just after 1/e
    std::vector<double> fib= generate_fibonacci_till(1./e); 
    int n= fib.size() - 3;  // no. of iterations in fibonacci search
    double a0= a, b0= b;

    // running variables
    double L= b-a;
    double r= fib[n+1]/fib[n+2];
    double ad= a + (1-r)*L, bd= b - (1-r)*L;
    double fa= f(ad), fb= f(bd);

    for (int i=1;i<=n;i++){
        if (fa <= fb){
            b= bd;
            bd= ad, fb= fa;
            L= b-a;
            r= fib[n+1-i]/fib[n+2-i];
            ad= a+ (1-r)*L, fa= f(ad);
        }
        else{
            a= ad;
            ad= bd, fa= fb;
            L= b-a;
            r= fib[n+1-i]/fib[n-i+2];
            bd= b- (1-r)*L, fb= f(bd);
        }
    }

    printf("No.of iteration of fibonacci_serach(..., %0.2f, %0.2f, ...) = %d\n", a0, b0, n);
    printf("The minimum occurs at: [%0.5f]\n", (a+b)/2);
    printf("The minimum value is: [%0.5f]\n\n", f((a+b)/2));
    return (a+b)/2;
}



/**
 * @param f is a std::function for f
 * @param df is a std::function that is the derivitive of f
 * @param a,b are the initial search bracket end points, ie we search for min in [a,b]
 * @param e is the tolerance parameter, default value is 10^-5
 * @brief does fibonacci search assuming that f is unimodal.
 */
double bisection_search(
    const std::function<double(double)>& f,
    const std::function<double(double)>& df,
    double a, double b,  
    double e= 1e-5
){
    if(a > b) throw std::runtime_error("Provide proper interval [a,b] where a <= b\n");

    using ll= long long;
    ll n= ll(log(e)/log(0.5));

    double a0= a, b0= b;

    // running variables
    double L= b-a;
    
    while(L > e){
        double x= (a+b)/2;
        if(df(x)== 0.0) return x;
        else if(df(x) > 0.0) b= x;
        else a= x;
        L= b-a;
    }

    printf("No.of iteration of bisection_serach(..., %0.2f, %0.2f, ...) = %lld\n", a0, b0, n);
    printf("The minimum occurs at: [%0.5f]\n", (a+b)/2);
    printf("The minimum value is: [%0.5f]\n\n", f((a+b)/2));
    return (a+b)/2; 
}


