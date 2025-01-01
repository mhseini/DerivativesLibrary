//
//  CRRPricer.h
//  Derivatives lib
//
//  Created by Mohammed Hseini on 07/11/2024.
//
#pragma once
#include "Option.h"
#include "BinaryTree.h"

double binomialCoefficient(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;

    double coeff = 1.0;
    for (int i = 1; i <= k; ++i) {
        coeff *= (n - i + 1) / static_cast<double>(i);
    }
    return coeff;
}
class CRRPricer
{
    public :
    CRRPricer(Option* option, int depth, double asset_price, double up,
    double down, double interest_rate)
    {
        if (down >= interest_rate ||  interest_rate >=up  ) throw std::invalid_argument("invalid argument : arbitrage ");
        
        if (option->isAsianOption()){
            throw("invalid option type : asian options not supported");
        }
        _option = option;
        _depth=depth;
        _underlying_tree.setDepth(depth);
        _price_tree.setDepth(depth);
        _exercise.setDepth(depth);
        _interest_rate= interest_rate;
        _up = up;
        _down = down;
        _asset_price = asset_price;
    }
    
    
    CRRPricer(Option* option, int depth, double asset_price, double r, double volatility){
        
        if (option->isAsianOption()){
            throw("invalid option type : asian options not supported");
        }
        _option = option;
        _depth=depth;
        _underlying_tree.setDepth(depth);
        _price_tree.setDepth(depth);
        _exercise.setDepth(depth);
        _asset_price = asset_price;
        
        double h = _option->getExpiry()/ _depth ;
        _up= std::exp( (r + volatility*volatility/2) *h + volatility*std::sqrt(h) ) -1;
        _down = std::exp( (r + volatility*volatility/2) *h - volatility*std::sqrt(h) ) -1;
        _interest_rate = std::exp(r*h) -1;
        
    }
    
    void compute() {
        // fill  underlying tree with values (forward pass)
        for (int level =0 ; level <_depth+1; level++)
        {
            for ( int pos = 0 ; pos < level+1; pos++)
            {
                double value = _asset_price*std::pow(1+_up, pos)*std::pow(1+_down, level-pos);
                _underlying_tree.setNode(level, pos, value);
            }
        }
        // fill price tree backward pass
        //first for expiry
        for (int pos=0 ; pos <_depth+1; pos++){
            double value = _option->payoff(_underlying_tree.getNode(_depth, pos));
            _price_tree.setNode(_depth, pos, value);
            _exercise.setNode(_depth, pos, value >= 0 ?  true: false);
        }
        // implement recursion logic
        double q = (_interest_rate - _down) / ( _up - _down);
        if ( _depth > 0) {
            for ( int level =  _depth - 1; level >=0; level--){
                for ( int pos = 0 ; pos < level+1 ; pos++){
                    double price_up = _price_tree.getNode(level+1, pos+1);
                    double price_down = _price_tree.getNode(level+1, pos);
                    double price = (q*price_up +(1-q)*price_down)/ (1.0+_interest_rate);
                    if (!_option->isAmericanOption())
                    {_price_tree.setNode(level, pos, price);}
                    else {
                        double intrinsicValue = _option->payoff(_underlying_tree.getNode(level,pos));
                        _price_tree.setNode(level, pos, std::max(price, intrinsicValue));
                        _exercise.setNode(level,pos, intrinsicValue >= price ? true : false);
                    }
                }
            }
        }
    }
    double get ( int level , int pos){
        return _price_tree.getNode(level, pos);
    }
    double operator()(bool closed_form=false){
        compute();
        if (closed_form && !_option->isAmericanOption()){
            double price =0.0;
            double q = (_interest_rate - _down) / ( _up - _down);
            double discount = 1.0/std::pow( 1+_interest_rate, _depth);
            for ( int pos =0 ; pos<_depth+1; pos++){
                double payoff = _option->payoff(_underlying_tree.getNode(_depth, pos));
                double factor = binomialCoefficient(_depth, pos) * std::pow(q, pos) * std::pow(1 - q, _depth - pos);
                
                price+= factor * payoff;
            }
            price*=discount;
            return price;
        }
        else
        {
            return _price_tree.getNode(0,0);
        }
    }
    
    bool getExercise(int level , int pos){
        return _exercise.getNode(level, pos);
    }
    
    private :
    BinaryTree<double> _underlying_tree;
    BinaryTree<double> _price_tree;
    BinaryTree<bool> _exercise;
    Option* _option;
    double _depth;
    double _interest_rate;
    double _up;
    double _down;
    double _asset_price;
    
    
};
