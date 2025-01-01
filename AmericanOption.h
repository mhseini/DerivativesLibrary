//
//  AmericanOption.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 14/11/2024.
//

#pragma once
#include "Option.h"

class AmericanOption : public Option
{
public:
    AmericanOption(double expiry): Option(expiry) {};
    bool isAmericanOption () override{
        return true;
    }

};

