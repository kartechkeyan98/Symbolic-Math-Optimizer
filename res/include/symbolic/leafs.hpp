#pragma once

#include<symbolic/expression.hpp>

namespace symbolic{

/** Leaf Nodes */
class Constant: public Expression{
private:
    double value;
public:
    Constant(double v): value(v){}
    double evaluate(const env& vars)const override{
        return value;
    }
    double item()const{return value;}

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        std::string s= std::to_string(value);
        s.erase(s.find_last_not_of('0') + 1, std::string::npos);
        if(s.back()=='.')s.pop_back();
        return s;
    }

    // visuals routines!
    std::string get_label()const override{
        std::string s= std::to_string(value);
        s.erase(s.find_last_not_of('0') + 1, std::string::npos);
        if(s.back()=='.')s.pop_back();
        return s;
    }
};
class Variable: public Expression{
private:
    std::string name;
public:
    Variable(const std::string &varname): name(varname){}
    double evaluate(const env& vars)const override{
        if(vars.find(name)==vars.end()){
            throw std::runtime_error("Variable not found in environment: "+name);
        }
        return vars.at(name);
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return name;
    }

    // visuals routines!
    std::string get_label()const override{return name;}
};

// factory functions for the DSL
expr constant(double val){return std::make_shared<Constant>(val);}
expr variable(const std::string &name){return std::make_shared<Variable>(name);}

// differentiation routines!
expr Constant::diff(const std::string &varname)const{
    return constant(0.0);
}
expr Variable::diff(const std::string &varname)const{
    if(name==varname)return constant(1.0);
    return constant(0.0);
}

template <typename T>
std::shared_ptr<T> match(expr e) {
    return std::dynamic_pointer_cast<T>(e);
}

// --- Helper: Constant Checking ---
// Returns true if 'e' is a constant with value 'val'
bool is_val(expr e, double val) {
    auto c = match<Constant>(e);
    return c && std::abs(c->item() - val) < 1e-9;
}

// Returns pointer to Constant if e is one, else nullptr
std::shared_ptr<Constant> as_const(expr e) {
    return match<Constant>(e);
}


}