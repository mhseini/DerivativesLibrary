
#pragma once
#include "Option.h"

class AsianOption : public Option
{
public:
    AsianOption(std::vector<double> timeSteps) : Option(timeSteps.size()), _timeSteps(timeSteps) {};
    
    std::vector<double> getTimeSteps(){
        return _timeSteps;
    }
    
    double payoffPath(std::vector<double> path) override
     {
         double z =0;
         for ( int i=0 ; i<path.size(); i++){
             z+= path[i];
         }
         z/= path.size();
         return payoff(z);
     };
    
private:
    std::vector<double> _timeSteps;
};

