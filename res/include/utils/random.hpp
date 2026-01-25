#pragma once

#include<random>
#include<vector>

class random_generator{
private:
    std::mt19937 gen_;

public:
    random_generator()
    : gen_(std::random_device{}())  // seed the random engine
    {}

    // generate random double uniformly, in range [mn, mx)
    double uniform_random_double(double mn, double mx){
        std::uniform_real_distribution<double> dist(mn, mx);
        return dist(gen_);
    }
    // generate uniform random ints, b/w [mn, mx]
    int uniform_random_int(int mn, int mx){
        std::uniform_int_distribution<int> dist(mn, mx);
        return dist(gen_);
    }
    // generate number sampled from N(mu, var)
    double gaussian_random_double(double mu, double stddev){
        std::normal_distribution<double> dist(mu, stddev);
        return dist(gen_);
    }

    // custom finite discrete distribution
    double discrete_distro(const std::vector<double>& pmf){
        std::discrete_distribution<int> dist(pmf.begin(), pmf.end());
        return dist(gen_);
    }
    // custom piecewise

    // full custom from cdf

};