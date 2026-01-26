#pragma once

// base class includes
#include<symbolic/expression.hpp>
#include<symbolic/leafs.hpp>
#include<symbolic/math.hpp>

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

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "sin";}
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

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "cos";}
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

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "tan";}
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

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "sec";}
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

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "csc";}
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

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "cot";}
};

// 2. Inverse Trig Operations
class Asin: public Expression{
private:
    expr arg;
public:
    Asin(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        double val= arg->evaluate(vars);
        if(val < -1.0 || val > 1.0){
            throw std::domain_error("asin domain error: value must be in [-1, 1]");
        }
        return std::asin(val);
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "asin(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "asin";}
};
class Acos: public Expression{
private:
    expr arg;
public:
    Acos(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        double val= arg->evaluate(vars);
        if(val < -1.0 || val > 1.0){
            throw std::domain_error("asin domain error: value must be in [-1, 1]");
        }
        return std::acos(val);
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "acos(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "acos";}
};
class Atan: public Expression{
private:
    expr arg;
public:
    Atan(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        double val= arg->evaluate(vars);
        return std::atan(val);
    }

    expr diff(const std::string &varname)const override;
    std::string toString()const override{
        return "atan(" + arg->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "atan";}
};

/** Factory Functions */
// 1. Trig ops
expr sin(expr arg){return std::make_shared<Sin>(arg);}
expr cos(expr arg){return std::make_shared<Cos>(arg);}
expr tan(expr arg){return std::make_shared<Tan>(arg);}
expr csc(expr arg){return std::make_shared<Csc>(arg);}
expr sec(expr arg){return std::make_shared<Sec>(arg);}
expr cot(expr arg){return std::make_shared<Cot>(arg);}

// 2. Inverse Trig Ops
expr asin(expr arg){return std::make_shared<Asin>(arg);}
expr acos(expr arg){return std::make_shared<Acos>(arg);}
expr atan(expr arg){return std::make_shared<Atan>(arg);}

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

// 2. Inverse Trig Functions
expr Asin::diff(const std::string &varname)const{
    //d[asin(x)] = dx / sqrt(1-x^2)
    expr u = arg;
    expr du= u->diff(varname);

    expr D= constant(1.) - (u ^ 2.0);
    return du/sqrt(D);
}
expr Acos::diff(const std::string &varname)const{
    //d[acos(x)] = -dx / sqrt(1-x^2)
    expr u = arg;
    expr du= u->diff(varname);

    expr D= constant(1.) - (u ^ 2.0);
    return constant(-1.)*du/sqrt(D);
}
expr Atan::diff(const std::string &varname)const{
    //d[atan(x)] = dx / (1 + x^2)
    expr u = arg;
    expr du= u->diff(varname);

    expr D= constant(1.) + (u ^ 2.0);
    return du/D;
}

}