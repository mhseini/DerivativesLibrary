//
//  EuropeanDigitalOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 08/11/2024.
//

#pragma once
#include "Option.h"


class EuropeanDigitalOption : public Option
{
    private :
    double _strike;
    
    public :
    EuropeanDigitalOption(double expiry, double strike) : Option(expiry), _strike(strike)
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




