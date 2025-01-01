//
//  MT.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 12/11/2024.
//

#pragma once
#include "random"

class MT
{
    public :

    static MT& instance() {
        static MT instance;
        return instance;
    }
    static double rand_unif(){
        return instance()._uniform(instance()._MT);
    };
    static double rand_norm(){
        return instance()._normal(instance()._MT);
    };
    
    private :
    // private constructor
    MT() : _MT(1), _uniform(0.0,1.0) , _normal(0.0,1.0) {};
    
    std::mt19937 _MT;
    std::uniform_real_distribution<> _uniform;
    std::normal_distribution<> _normal;
    
    MT(const MT&) = delete;            // Prevent copy construction
    MT& operator=(const MT&) = delete; // prevent copy assignment 
    
    // delete copy constructor and assignement operator to enforce singleton behavior
    
};
