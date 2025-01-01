//
//  EuropeanDigitalCallOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 15/11/2024.
//

#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalCallOption :  public EuropeanDigitalOption {
    
    public :
    EuropeanDigitalCallOption(double expiry, double strike) : EuropeanDigitalOption(expiry,strike){};

    optionType getOptionType() override{
        return optionType::digitalCall;
    }
    
    double payoff(double z ) override final {
        return (z-getStrike()) > 0 ? 1 :  0;
    }
    
    
    
};
