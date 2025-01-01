//
//  BlackScholesMCPricer.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 12/11/2024.
//
#pragma once

#include "MT.h"
#include "Option.h"
#include "AsianOption.h"

class BlackScholesMCPricer {
public:
    BlackScholesMCPricer(Option* option, double initial_price, double interest_rate, double volatility)  {
        _option = option;
        _initial_price=initial_price;
        _interest_rate = interest_rate;
        _volatility=volatility;
        _nbPaths = 0;
        _price = 0.0;
        _sumPrices =0.0;
        _squareSumPrices =0.0;
        
        if (AsianOption* asian = dynamic_cast<AsianOption*>(_option)){
            _timeSteps = asian->getTimeSteps();
        }
        else {
            _timeSteps.push_back(_option->getExpiry());
        }
        
        
    };
    
    double getNbPaths() {
        return _nbPaths;
    }
    void generate(int nb_paths){
            std::vector<double> tmpPath;
            double discount =  std::exp(-_interest_rate*_timeSteps[_timeSteps.size()-1]);
            for ( int i=0; i< nb_paths; i++){
                double s_k = _initial_price;
                double t_k =0.0;
                for ( double k = 0 ; k < _timeSteps.size();  k++){
                    double z = MT::rand_norm();
                    double s = s_k *std::exp((_interest_rate-(_volatility*_volatility)/2.0)*(_timeSteps[k]-t_k) + _volatility* std::sqrt(_timeSteps[k]-t_k) * z);
                    tmpPath.push_back(s);
                    s_k =s;
                    t_k = _timeSteps[k];
                    }
                double pathPrice =_option->payoffPath(tmpPath);
                tmpPath.clear();
                ++_nbPaths;
                double discountedPrice =discount* pathPrice;
                _sumPrices += discountedPrice;
                _squareSumPrices += discountedPrice * discountedPrice;
            }
        _price = _sumPrices / _nbPaths;
        };
    
    double operator()(){
        // THROW AN EXCEPTION IF _PRICE IS UNDEFINED
        return _price;
        
    }
    
   
    std::vector<double> confidenceInterval()
    {
        std::vector<double> res;
    
       // double variance = (1.0/(_nbPaths-1)) *(_squareSumPrices + _nbPaths*_price*_price-2*_price*_sumPrices);
        double variance = (_squareSumPrices - _nbPaths * _price * _price) / (_nbPaths - 1);

        res.push_back(_price-1.96*std::sqrt(variance/_nbPaths));
        res.push_back(_price+1.96*std::sqrt(variance/_nbPaths));
        
        return res;
    }
    
     
    private :
    Option* _option;
    double _price;
    std::vector<double> _timeSteps;
    double _sumPrices;
    double _squareSumPrices;
    double _initial_price;
    double _interest_rate;
    double _volatility;
    int _nbPaths; // since the beginning of the program. How to do this ?
    
    
};
