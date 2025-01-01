//
//  
//  Derivatives lib
//
//  Created by Mohammed Hseini on 08/11/2024.
//

#pragma once

#include "EuropeanVanillaOption.h"
#include "EuropeanDigitalOption.h"

class BlackScholesPricer
{
    public :
    BlackScholesPricer(Option* option, double asset_price,
                           double interest_rate, double volatility) :
            _option(option), _asset_price(asset_price), _interest_rate(interest_rate),_volatility(volatility)
    {
        
        if (EuropeanDigitalOption* digitalOption = dynamic_cast<EuropeanDigitalOption*>(_option)){
            _strike = digitalOption->getStrike();
            _optType = digitalOption->getOptionType();
        }

        else if (EuropeanVanillaOption* vanilla= dynamic_cast<EuropeanVanillaOption*>(_option)){
            _strike = vanilla->getStrike();
            _optType = vanilla->getOptionType();
        }
    } ;
    


    double operator()()
    {
        
        double expiry = _option-> getExpiry();
        
        double d1 = (std::log(_asset_price/ _strike) +
                     (_interest_rate + _volatility*_volatility/2.0)*expiry)/(_volatility* std::sqrt(expiry));
        double d2 = d1 - _volatility*std::sqrt(expiry);
        
        if (_optType == optionType::call) {
            return _asset_price*normalCDF(d1) - _strike*std::exp(-_interest_rate*expiry)*normalCDF(d2);
        }
        else if (_optType == optionType::put) return _strike*std::exp(-_interest_rate*expiry)*normalCDF(-d2) - _asset_price*normalCDF(-d1);
        
        else if (_optType ==optionType::digitalCall) return std::exp(-_interest_rate*expiry)*normalCDF(d2);
        else if (_optType == optionType::digitalPut) return std::exp(-_interest_rate*expiry)*normalCDF(-d2) ;
        
    
        else return 0;
    };
    
    double delta(){
        
        double expiry = _option-> getExpiry();
        double d1 = (std::log(_asset_price/ _strike) +
                     (_interest_rate + _volatility*_volatility/2.0)*expiry)/(_volatility* std::sqrt(expiry));
        
        double d2 = d1 - _volatility*std::sqrt(expiry);
        if (_optType == optionType::call){
            return normalCDF(d1);
        }
        else if ( _optType== optionType::put) return -normalCDF(-d1);
        else if ( _optType== optionType::digitalCall) return
            (std::exp(-_interest_rate*expiry)*normalDensity(d2))/(_asset_price*_volatility*std::sqrt(expiry));
        
        else if (_optType== optionType::digitalPut) return
            -(std::exp(-_interest_rate*expiry)*normalDensity(d2))/(_asset_price*_volatility*std::sqrt(expiry));
    
        else return 0;
    }
    
    private :
        Option* _option;
        optionType _optType;
        double _strike;
        double _asset_price;
        double _interest_rate;
        double _volatility ;
};
