#pragma once

#include<vector>

/**
 * @param n the no.of fibonacci number you wanna generate 
 * @brief This function generates fibonacci no.s with indices
 * f0 = 0, f1 = 1, f2= 2..... fn, hence returning n+1 values
 */
std::vector<double> generate_fibonacci_numbers(int n){
    std::vector<double> fib(n+1);
    fib[0]= 0.0, fib[1]= 1.0;
    for(int i=2;i<n+1;i++)fib[i]= fib[i-1] + fib[i-2];
    return fib;
}

/**
 * @param x the number after which functions stops generating
 * @brief This function generates fibonacci numbers till just after x
 * f0 = 0, f1 = 1, f2= 2..... fn, hence returning n+1 values
 */
std::vector<double> generate_fibonacci_till(double x){
    std::vector<double> fib(2);
    fib[0]= 0.0, fib[1]= 1.0;
    long long c= 1;
    while(fib[c] <= x){
        fib.push_back(fib[c]+fib[c-1]);
        ++c;
    }
    return fib;
}