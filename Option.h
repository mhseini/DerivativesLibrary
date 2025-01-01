//
//  Option.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 23/10/2024.
//

#pragma once

#include "math.h"

enum class optionType {call , put, digitalCall, digitalPut };

inline double normalCDF(double x)
{
    return std::erfc(-x / std::sqrt(2)) / 2;
};

inline double normalDensity(double x)
{
    
    return (1.0/ std::sqrt(2*M_PI))*std::exp((-x*x)/2.0);
    
}
class Option
{
    private :
        double _expiry;
    public :
    Option (double expiry) : _expiry (expiry){};
    virtual ~Option() = default;
    double getExpiry(){  return _expiry;};
    virtual double payoff (double ) = 0;
    virtual double payoffPath (std::vector<double> path) {
        return payoff(path[path.size()-1]);
    };
    
    virtual bool isAsianOption(){
        return false;
    };
    
    virtual bool isAmericanOption() {
        return false;
    }
};
