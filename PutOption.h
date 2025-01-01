//
//  PutOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 15/11/2024.
//

#pragma once
#include "EuropeanVanillaOption.h"

class PutOption : public EuropeanVanillaOption {
    public :
    PutOption(double expiry, double strike) : EuropeanVanillaOption(expiry,strike){};

    
    optionType getOptionType() override{
        return optionType::put;
    }
    
  double payoff(double z ) override final{
        return (getStrike()-z) > 0 ? getStrike()-z :  0;
    }
};
