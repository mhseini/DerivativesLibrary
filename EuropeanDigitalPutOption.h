//
//  EuropeanDigitalPutOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 15/11/2024.
//

#pragma once
#include "EuropeanDigitalOption.h"

class EuropeanDigitalPutOption : public EuropeanDigitalOption {
    public :
    EuropeanDigitalPutOption(double expiry, double strike) : EuropeanDigitalOption(expiry,strike){};

    
    optionType getOptionType() override{
        return optionType::digitalPut;
    }
    
  double payoff(double z ) override final{
        return (getStrike()-z) > 0 ? 1 :  0;
    }
};
