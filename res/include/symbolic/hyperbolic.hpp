#pragma once

#include<symbolic/expression.hpp>
#include<symbolic/leafs.hpp>
#include<symbolic/math.hpp>
#include<symbolic/trig.hpp>

// math for evaluation routines
#include<cmath>

namespace symbolic{

/** Hyperbolic Operations */
// 1. Standard Hyperbolic functions
class Sinh: public Expression{
private:
    expr arg;
public:
    Sinh(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::sinh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "sinh(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "sinh";}
};
class Cosh: public Expression{
private:
    expr arg;
public:
    Cosh(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::cosh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "cosh(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "cosh";}
};
class Tanh: public Expression{
private:
    expr arg;
public:
    Tanh(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::tanh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "tanh(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "tanh";}
};
class Sech: public Expression{
private:
    expr arg;
public:
    Sech(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return 1./std::cosh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "sech(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "sech";}
};
class Csch: public Expression{
private:
    expr arg;
public:
    Csch(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return 1./std::sinh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "csch(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "csch";}
};
class Coth: public Expression{
private:
    expr arg;
public:
    Coth(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return 1./std::tanh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "coth(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "coth";}
};

// 2. Inverse Hyperbolic functions
class Asinh: public Expression{
private:
    expr arg;
public:
    Asinh(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::asinh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "asinh(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "asinh";}
};
class Acosh: public Expression{
private:
    expr arg;
public:
    Acosh(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        double val = arg->evaluate(vars);
        if (val < 1.0) throw std::domain_error("acosh domain error: value must be >= 1");
        return std::acosh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "acosh(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "acosh";}
};
class Atanh: public Expression{
private:
    expr arg;
public:
    Atanh(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        double val = arg->evaluate(vars);
        if (val <= -1.0 || val >= 1.0) {
            throw std::domain_error("atanh domain error: value must be in (-1, 1)");
        }
        return std::atanh(arg->evaluate(vars));
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "atanh(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "atanh";}
};


/** Factory Functions */
// 1. Hyperbolic functions
expr sinh(expr arg){return std::make_shared<Sinh>(arg);}
expr cosh(expr arg){return std::make_shared<Cosh>(arg);}
expr tanh(expr arg){return std::make_shared<Tanh>(arg);}
expr csch(expr arg){return std::make_shared<Csch>(arg);}
expr sech(expr arg){return std::make_shared<Sech>(arg);}
expr coth(expr arg){return std::make_shared<Coth>(arg);}

// 2. Inverse Hyperbolic functions
expr asinh(expr arg){return std::make_shared<Asinh>(arg);}
expr acosh(expr arg){return std::make_shared<Acosh>(arg);}
expr atanh(expr arg){return std::make_shared<Atanh>(arg);}


/** Diffentiation Operators */
// 1. Hyperbolic Functions
expr Sinh::diff(const std::string& varname)const{
    // d[sinh(x)] = cosh(x) * dx
    return cosh(arg) * arg->diff(varname);
}
expr Cosh::diff(const std::string& varname)const{
    // d[cosh(x)] = sinh(x) * dx
    return sinh(arg) * arg->diff(varname);
}
expr Tanh::diff(const std::string& varname)const{
    // d[tanh(x)] = sech^2(x) * dx
    expr u = arg;
    expr du= u->diff(varname);
    return (sech(u)^2)*du;
}
expr Sech::diff(const std::string& varname)const{
    // d[sech(x)] = -sech(x) * tanh(x) * dx
    expr u = arg;
    expr du= u->diff(varname);
    return constant(-1) * sech(u) * tanh(u) * du;
}
expr Csch::diff(const std::string& varname)const{
    // d[csch(x)] = -csch(x) * coth(x) * dx
    return constant(-1) * csch(arg) * coth(arg) * arg->diff(varname);
}
expr Coth::diff(const std::string& varname)const{
    // d[coth(x)] = -csch^2(x) * dx
    return constant(-1) * (csch(arg) ^ 2) * arg->diff(varname);
}

// 2. Inverse Hyperbolic Functions
expr Asinh::diff(const std::string& varname)const{
    // d[asinh(x)] = dx / sqrt(1 + x^2)
    expr u = arg;
    expr du= arg->diff(varname);
    expr D= sqrt((u ^ 2.0) + constant(1.));
    return du / D;
}
expr Acosh::diff(const std::string& varname)const{
    // d[acosh(x)] = dx / sqrt(x^2 - 1)
    expr u = arg;
    expr du= arg->diff(varname);
    expr D= sqrt((u ^ 2.0) - constant(1.));
    return du / D;
}
expr Atanh::diff(const std::string& varname)const{
    // d[asinh(x)] = dx / (1 - x^2)
    expr u = arg;
    expr du= arg->diff(varname);
    return du / (constant(1.) - u^2.);
}


}