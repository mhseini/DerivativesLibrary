//
//  AmericanPutOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 15/11/2024.
//

#pragma once
#include "AmericanOption.h"

class AmericanPutOption : public AmericanOption
{
public:
    AmericanPutOption(double expiry, double strike): AmericanOption(expiry), _strike(strike) {};
    
    double payoff(double z) override{
        return (_strike-z)> 0 ?  _strike-z : 0;
    }
private :
    double _strike;
    
};
