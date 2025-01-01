
#pragma once
#include "AsianOption.h"

class AsianCallOption : public AsianOption{
public:
    AsianCallOption(std::vector<double> timeSteps, double strike ) : AsianOption(timeSteps) {
        _strike = strike;
    };
    
    double payoff(double z) override  {
        return (z-_strike) > 0 ? z - _strike :  0;
    }
    
    bool isAsianOption() override {
        return true;
    }
    
    private :
    double _strike;
};
