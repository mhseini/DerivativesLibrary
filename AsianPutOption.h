
#pragma once
#include "AsianOption.h"

class AsianPutOption : public AsianOption{
public:
    AsianPutOption(std::vector<double> timeSteps, double strike ) : AsianOption(timeSteps) {
        _strike = strike;
    };
    
    double payoff(double z) override  {
        return (_strike-z) > 0 ?  _strike - z :  0;
    }
    
    bool isAsianOption() override {
        return true;
    }
    
    private :
    double _strike;
};
