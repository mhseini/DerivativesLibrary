//
//  CallOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 15/11/2024.
//

#pragma once
#include "EuropeanVanillaOption.h"

class CallOption :  public EuropeanVanillaOption {
    
    public :
    CallOption(double expiry, double strike) : EuropeanVanillaOption(expiry,strike){};

    optionType getOptionType() override{
        return optionType::call;
    }
    
    double payoff(double z ) override final {
        return (z-getStrike()) > 0 ? z - getStrike() :  0;
    }
    
    
    
};
