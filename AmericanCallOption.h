//
//  AmericanCallOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 15/11/2024.
//
#pragma once
#include "AmericanOption.h"

class AmericanCallOption : public AmericanOption{
public:
    AmericanCallOption(double expiry, double strike): AmericanOption(expiry), _strike(strike) {};
    
    double payoff(double z) override{
        return (z-_strike)> 0 ?  z-_strike : 0;
    }
private :
    double _strike;
};

