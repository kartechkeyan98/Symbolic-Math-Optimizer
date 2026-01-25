#pragma once

// base class includes
#include<symbolic/expression.hpp>
#include<symbolic/leafs.hpp>
#include<symbolic/basicops.hpp>

// std libs
#include<cmath>

namespace symbolic{

/** Complex Math Operations */
// 1. Trig Operations
class Sin: public Expression{
private:
    expr arg;
public:
    Sin(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::sin(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "sin(" + arg->toString() + ")";
    }
};
class Cos: public Expression{
private:
    expr arg;
public:
    Cos(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::cos(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "cos(" + arg->toString() + ")";
    }
};
class Tan: public Expression{
private:
    expr arg;
public:
    Tan(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::tan(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "tan(" + arg->toString() + ")";
    }
};
class Sec: public Expression{
private:
    expr arg;
public:
    Sec(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return 1./std::cos(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "sec(" + arg->toString() + ")";
    }
};
class Csc: public Expression{
private:
    expr arg;
public:
    Csc(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return 1./std::sin(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "csc(" + arg->toString() + ")";
    }
};
class Cot: public Expression{
private:
    expr arg;
public:
    Cot(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return 1./std::tan(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "cot(" + arg->toString() + ")";
    }
};

// 2. Inverse Trig Operations





/** Factory Functions */
// 1. Trig ops
expr sin(expr arg){return std::make_shared<Sin>(arg);}
expr cos(expr arg){return std::make_shared<Cos>(arg);}
expr tan(expr arg){return std::make_shared<Tan>(arg);}
expr csc(expr arg){return std::make_shared<Csc>(arg);}
expr sec(expr arg){return std::make_shared<Sec>(arg);}
expr cot(expr arg){return std::make_shared<Cot>(arg);}

// 2. Inverse Trig Ops

// ---- Differentiation Ops ---- //
// 1. Trig Functions!
expr Sin::diff(const std::string& varname)const{
    // d[sin(x)] = cos(x) * dx
    return cos(arg) * arg->diff(varname);
}
expr Cos::diff(const std::string& varname)const{
    // d[cos(x)] = -sin(x) * dx
    return constant(-1) * cos(arg) * arg->diff(varname);
}
expr Tan::diff(const std::string& varname)const{
    // d[tan(x)] = sec^2(x) * dx
    expr u = arg;
    expr du= u->diff(varname);
    return (sec(u)^2)*du;
}
expr Sec::diff(const std::string& varname)const{
    // d[sec(x)] = sec(x) * tan(x) * dx
    expr u = arg;
    expr du= u->diff(varname);
    return sec(u) * tan(u) * du;
}
expr Csc::diff(const std::string& varname)const{
    // d[csc(x)] = -csc(x) * cot(x) * dx
    return constant(-1) * csc(arg) * cot(arg) * arg->diff(varname);
}
expr Cot::diff(const std::string& varname)const{
    return constant(-1) * (csc(arg) ^ 2) * arg->diff(varname);
}

}