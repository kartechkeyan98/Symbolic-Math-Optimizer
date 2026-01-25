#pragma once

#include<iostream>
#include<memory>
#include<map>

namespace symbolic{

class Expression;

using expr= std::shared_ptr<Expression>;
// used to store variable nodes only!
using env = std::map<std::string, double>;

class Expression{
public:
    virtual double evaluate(const env& vars)const = 0;
    virtual expr diff(const std::string &varname)const = 0;
    virtual std::string toString()const= 0;
    virtual ~Expression()= default;
};


}