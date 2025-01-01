//
//  EuropeanVanillaOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 23/10/2024.
//

#pragma once
#include "Option.h"


class EuropeanVanillaOption : public Option
{
    private :
    double _strike;
    
    public :
    EuropeanVanillaOption(double expiry, double strike) : Option(expiry), _strike(strike)
    {
        if (expiry < 0 ) throw std::invalid_argument("expiry is negative");
        if ( strike <0 ) throw std::invalid_argument ("strike is negative");
    };
    
    
    virtual optionType getOptionType() =0;
    
    double getStrike() {
        return _strike;
    }
    
    friend class BlackScholesPricer;
};



