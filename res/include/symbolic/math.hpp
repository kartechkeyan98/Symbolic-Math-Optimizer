#pragma once

#include<symbolic/expression.hpp>
#include<symbolic/leafs.hpp>

#include<cmath>

namespace symbolic{

/** Operation Nodes */

// Basic Operations
class Add: public Expression{
private:
    expr left, right;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Add(expr l, expr r): left(std::move(l)), right(std::move(r)){}
    double evaluate(const env& vars)const override{
        return left->evaluate(vars) + right->evaluate(vars);
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "("+left->toString() + " + " + right->toString() + ")";
    }

    // visuals routines!
    std::vector<expr> get_children()const override{return {left, right};}
    std::string get_label()const override{return "+";}
};
class Sub: public Expression{
private:
    expr left, right;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Sub(expr l, expr r): left(std::move(l)), right(std::move(r)){}
    double evaluate(const env& vars)const override{
        return left->evaluate(vars) - right->evaluate(vars);
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "("+left->toString() + " - " + right->toString() + ")";
    } 
    
    // visuals routines!
    std::vector<expr> get_children()const override{return {left, right};}
    std::string get_label()const override{return "-";}
};
class Mul: public Expression{
private:
    expr left, right;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Mul(expr l, expr r): left(std::move(l)), right(std::move(r)){}
    double evaluate(const env& vars)const override{
        return left->evaluate(vars) * right->evaluate(vars);
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "("+left->toString() + " * " + right->toString() + ")";
    }   
    
    // visuals routines!
    std::vector<expr> get_children()const override{return {left, right};}
    std::string get_label()const override{return "*";}
};
class Div: public Expression{
private:
    expr left, right;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Div(expr l, expr r): left(std::move(l)), right(std::move(r)){}
    double evaluate(const env& vars)const override{
        return left->evaluate(vars) / right->evaluate(vars);
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "("+left->toString() + " / " + right->toString() + ")";
    } 

    // visuals routines!
    std::vector<expr> get_children()const override{return {left, right};}
    std::string get_label()const override{return "/";}
};

// Complex Operations
class Pow: public Expression{
private:
    expr base, exponent;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Pow(expr b, expr e): base(std::move(b)), exponent(std::move(e)){}
    double evaluate(const env& vars)const override{
        return std::pow(base->evaluate(vars), exponent->evaluate(vars));
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "("+base->toString() + " ^ " + exponent->toString() + ")";
    } 

    // visuals routines!
    std::vector<expr> get_children()const override{return {base, exponent};}
    std::string get_label()const override{return "^";}
};
class Log: public Expression{
private:
    expr arg;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Log(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::log(arg->evaluate(vars));
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "log("+ arg->toString() + ")";
    } 
    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "log";}
};
class Exp: public Expression{
private:
    expr arg;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Exp(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::exp(arg->evaluate(vars));
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "exp("+arg->toString() + ")";
    }
    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "exp";} 
};
class Sqrt:public Expression{
private:
    expr arg;
public:
    // memory savings by using std::move since argument pointers
    // are passed by value! "Sink Argument" Pattern!
    Sqrt(expr a): arg(std::move(a)){}
    double evaluate(const env& vars)const override{
        return std::sqrt(arg->evaluate(vars));
    }

    expr diff(const std::string& varname)const override;
    std::string toString()const override{
        return "sqrt("+arg->toString()+ ")";
    } 

    // visuals routines!
    std::vector<expr> get_children()const override{return {arg};}
    std::string get_label()const override{return "sqrt";}
};


// Operator overloads for clean syntax (factory functions)
expr operator+(expr lhs, expr rhs){
    auto c1 = std::dynamic_pointer_cast<Constant>(lhs);
    auto c2 = std::dynamic_pointer_cast<Constant>(rhs);
    if (c1 && c2) return constant(c1->item() + c2->item());

    else if (is_val(lhs, 0.0)) return rhs;
    else if (is_val(rhs, 0.0)) return lhs;
    else if (lhs == rhs) return std::make_shared<Mul>(constant(2.), lhs);

    return std::make_shared<Add>(lhs, rhs);
}
expr operator-(expr lhs, expr rhs){
    auto c1 = std::dynamic_pointer_cast<Constant>(lhs);
    auto c2 = std::dynamic_pointer_cast<Constant>(rhs);
    if (c1 && c2) return constant(c1->item() - c2->item());

    if (is_val(lhs, 0.0)) return std::make_shared<Mul>(constant(-1.), rhs);
    else if (is_val(rhs, 0.0)) return lhs;
    else if (lhs == rhs) return constant(0.0);
    return std::make_shared<Sub>(lhs, rhs);
}
expr operator*(expr lhs, expr rhs){
    auto c1 = std::dynamic_pointer_cast<Constant>(lhs);
    auto c2 = std::dynamic_pointer_cast<Constant>(rhs);
    if (c1 && c2) return constant(c1->item() * c2->item());

    // simple speed ups
    if(is_val(lhs, 0.)||is_val(rhs,0.)) return constant(0.);
    else if(is_val(rhs, 1.0)) return lhs;
    else if(is_val(lhs, 1.0)) return rhs;
    else if(lhs == rhs) return std::make_shared<Pow>(lhs, constant(2));
    return std::make_shared<Mul>(lhs, rhs);
}
expr operator/(expr lhs, expr rhs){
    auto c1 = std::dynamic_pointer_cast<Constant>(lhs);
    auto c2 = std::dynamic_pointer_cast<Constant>(rhs);
    if (c1 && c2) return constant(c1->item() / c2->item());
    // simple speed ups
    if(is_val(lhs, 0.)) return constant(0.);
    else if(is_val(rhs, 1.0)) return lhs;
    else if (lhs == rhs) return constant(1.0);

    return std::make_shared<Div>(lhs, rhs);
}
expr operator^(expr lhs, expr rhs){
    auto c1 = std::dynamic_pointer_cast<Constant>(lhs);
    auto c2 = std::dynamic_pointer_cast<Constant>(rhs);
    if (c1 && c2) return constant(std::pow(c1->item(), c2->item()));

    if(is_val(rhs, 0)) return constant(1.);
    else if(is_val(lhs, 1)) return constant(1.);
    else if(is_val(rhs, 1)) return lhs;
    return std::make_shared<Pow>(lhs, rhs);
}


// Support for double literals! (ex- 2.0 * x, a= 4; a*x)
expr operator+(double lhs, expr rhs){return constant(lhs) + rhs;}
expr operator+(expr lhs, double rhs){return lhs + constant(rhs);}
expr operator-(double lhs, expr rhs){return constant(lhs) - rhs;}
expr operator-(expr lhs, double rhs){return lhs - constant(rhs);}
expr operator*(double lhs, expr rhs){return constant(lhs) * rhs;}
expr operator*(expr lhs, double rhs){return lhs * constant(rhs);}
expr operator/(double lhs, expr rhs){return constant(lhs) / rhs;}
expr operator/(expr lhs, double rhs){return lhs / constant(rhs);}

// more complex ones!
expr operator^(expr lhs, double rhs){return lhs ^ constant(rhs);}
expr operator^(double lhs, expr rhs){return constant(lhs) ^ rhs;}

// factory functions!
expr log(expr arg){return std::make_shared<Log>(arg);}
expr exp(expr arg){return std::make_shared<Exp>(arg);}
expr sqrt(expr arg){return std::make_shared<Sqrt>(arg);}

// ---- Differentiation Ops ---- //
// Basics Ops
expr Add::diff(const std::string &varname)const {
    return left->diff(varname) + right->diff(varname);
}
expr Sub::diff(const std::string &varname)const {
    return left->diff(varname) - right->diff(varname);
}
expr Mul::diff(const std::string &varname)const {
    return (left * right->diff(varname)) + (right * left->diff(varname)); 
}
expr Div::diff(const std::string &varname)const {
    expr u= left;
    expr v= right;
    expr du= left->diff(varname);
    expr dv= right->diff(varname);

    expr numerator= (v * du) - (u * dv);
    expr denominator= v * v;

    return numerator / denominator;
}

// Complex Ops
expr Pow::diff(const std::string &varname)const {
    // d[u^v] = u^v * (dv * ln(u) + v * du / u)
    expr u= base;
    expr v= exponent;
    expr du= u->diff(varname);
    expr dv= v->diff(varname);
    
    // optimization: if exponent is constant, the dv = 0
    if(auto c= std::dynamic_pointer_cast<Constant>(v)){
        // d[u^n] = n * u^(n-1) * du
        double n = c->item();
        if (std::abs(n) < 1e-8) {
            return constant(0.0);  // derivative of constant^something? Actually x^0 = 1
        }
        return constant(n) * (u ^ constant(n - 1.0)) * du;
    }

    auto const_deriv = std::dynamic_pointer_cast<Constant>(dv);
    if (const_deriv && std::abs(const_deriv->item()) < 1e-8) {
        // dv is zero, but we need the full formula? Actually if dv=0, v is constant wrt varname
        // So we can use the constant exponent formula
        return v * (u ^ (v - 1.0)) * du;
    }

    expr t1= dv * log(u);
    expr t2= v * (du / u);

    return std::make_shared<Pow>(u,v) * (t1 + t2);
}
expr Log::diff(const std::string &varname)const{
    // d[ln(u)] = du/u
    return arg->diff(varname)/arg;
}
expr Exp::diff(const std::string &varname)const{
    // d[e^x] = e^x * dx
    return exp(arg) * arg->diff(varname);
}
expr Sqrt::diff(const std::string & varname)const{
    // d[sqrt(x)] = dx/2*sqrt(x)
    return arg->diff(varname)/(constant(2.0)*std::make_shared<Sqrt>(arg));
}


}