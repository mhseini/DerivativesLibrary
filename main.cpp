//
//  main.cpp
//  Derivatives lib
//
//  Created by Mohammed Hseini on 23/10/2024.
//

#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AmericanCallOption.h"
#include "AmericanPutOption.h"
#include "CRRPricer.h"

/*
int main() {
    double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));
    opt_ptrs.push_back(new AmericanCallOption(T, K));
    opt_ptrs.push_back(new AmericanPutOption(T, K));

    CRRPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new CRRPricer(opt_ptr, 150, S0, r, sigma);

        pricer->compute();

        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;

    }
}
 */



//Test 2
#include <iostream>
#include <vector>
#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "AsianCallOption.h"
#include "AsianPutOption.h"
#include "BlackScholesMCPricer.h"


int main() {
    double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
    std::vector<Option*> opt_ptrs;
    opt_ptrs.push_back(new CallOption(T, K));
    opt_ptrs.push_back(new PutOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalCallOption(T, K));
    opt_ptrs.push_back(new EuropeanDigitalPutOption(T, K));

    std::vector<double> fixing_dates;
    for (int i = 1; i <= 5; i++) {
        fixing_dates.push_back(0.1*i);
    }
    opt_ptrs.push_back(new AsianCallOption(fixing_dates, K));
    opt_ptrs.push_back(new AsianPutOption(fixing_dates, K));

    std::vector<double> ci;
    BlackScholesMCPricer* pricer;

    for (auto& opt_ptr : opt_ptrs) {
        pricer = new BlackScholesMCPricer(opt_ptr, S0, r, sigma);
        do {
            pricer->generate(10);
            ci = pricer->confidenceInterval();
        } while (ci[1] - ci[0] > 1e-2);
        std::cout << "nb samples: " << pricer->getNbPaths() << std::endl;
        std::cout << "price: " << (*pricer)() << std::endl << std::endl;
        delete pricer;
        delete opt_ptr;
    }
}


/*
//Test 1
#include <iostream>

#include "CallOption.h"
#include "PutOption.h"
#include "EuropeanDigitalCallOption.h"
#include "EuropeanDigitalPutOption.h"
#include "BlackScholesPricer.h"
#include "CRRPricer.h"
#include "BinaryTree.h"


int main() {
    {

        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        CallOption opt1(T, K);
        PutOption opt2(T, K);


        std::cout << "European options 1" << std::endl << std::endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << std::endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << std::endl;
            std::cout << std::endl;

            int N(150);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;
            
            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer1() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << std::endl;
            std::cout << std::endl;

            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer2() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer2(true) << std::endl;
        }
        std::cout << std::endl << "*********************************************************" << std::endl;
    }

    {
        std::cout << "Binary Tree" << std::endl << std::endl;
        BinaryTree<bool> t1;
        t1.setDepth(3);
        t1.setNode(1, 1, true);
        t1.display();
        t1.setDepth(5);
        t1.display();
        t1.setDepth(3);
        t1.display();


        BinaryTree<double> t2;
        t2.setDepth(2);
        t2.setNode(2, 1, 3.14);
        t2.display();
        t2.setDepth(4);
        t2.display();
        t2.setDepth(3);
        t2.display();

        BinaryTree<int> t3;
        t3.setDepth(4);
        t3.setNode(3, 0, 8);
        t3.display();
        t3.setDepth(2);
        t3.display();
        t3.setDepth(4);
        t3.display();

        std::cout << std::endl << "*********************************************************" << std::endl;
    }

    {

        double S0(95.), K(100.), T(0.5), r(0.02), sigma(0.2);
        EuropeanDigitalCallOption opt1(T, K);
        EuropeanDigitalPutOption opt2(T, K);


        std::cout << "European options 2" << std::endl << std::endl;

        {
            BlackScholesPricer pricer1(&opt1, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer1() << ", delta=" << pricer1.delta() << std::endl;

            BlackScholesPricer pricer2(&opt2, S0, r, sigma);
            std::cout << "BlackScholesPricer price=" << pricer2() << ", delta=" << pricer2.delta() << std::endl;
            std::cout << std::endl;

            int N(150);
            double U = exp(sigma * sqrt(T / N)) - 1.0;
            double D = exp(-sigma * sqrt(T / N)) - 1.0;
            double R = exp(r * T / N) - 1.0;

            CRRPricer crr_pricer1(&opt1, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer1() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer1(true) << std::endl;
            std::cout << std::endl;

            CRRPricer crr_pricer2(&opt2, N, S0, U, D, R);
            std::cout << "Calling CRR pricer with depth=" << N << std::endl;
            std::cout << std::endl;
            std::cout << "CRR pricer computed price=" << crr_pricer2() << std::endl;
            std::cout << "CRR pricer explicit formula price=" << crr_pricer2(true) << std::endl;
        }
        std::cout << std::endl << "*********************************************************" << std::endl;
    }
}

*/
/*My Test
#include <iostream>
#include <iomanip>
#include "EuropeanVanillaOption.h"
#include "BinaryTree.h"
#include "CRRPricer.h"
#include "BlackScholesPricer.h"
#include"EuropeanDigitalOption.h"
#include "AsianOption.h"
#include "MT.h"
#include "BlackScholesMCPricer.h"
#include "AmericanOption.h"

int main(int argc, const char * argv[]) {
    // insert code here...
    //std::cout << "Hello, World!\n";
    

    BinaryTree<double> tree;
    tree.setDepth(3); // Set depth to 3 for example

    // Set some values in the tree
    tree.setNode(0, 0, 1.0);
    tree.setNode(1, 0, 1.1);
    tree.setNode(1, 1, 1.2);
    tree.setNode(2, 0, 1.3);
    tree.setNode(2, 1, 1.4);
    tree.setNode(2, 2, 1.5);
    tree.setNode(3, 0, 1.6);
    tree.setNode(3, 1, 1.7);
    tree.setNode(3, 2, 1.8);
    tree.setNode(3, 3, 1.9);

    // Display the tree
    tree.display();
    
    //option parameters
    double expiry = 1.0;
    double strike = 50.0;
    
    //BS model parmaters
    double asset_price = 100;
    double interest_rate = 0.01;
    double volatility = 0.10;
    
    // CRR paramaters
    int depth = 10;
    double h = expiry/ depth ;
    double up = std::exp( (interest_rate + volatility*volatility/2) *h + volatility*std::sqrt(h) ) -1;
    double down = std::exp( (interest_rate + volatility*volatility/2) *h - volatility*std::sqrt(h) ) -1;
    double R = std::exp(interest_rate*h) -1;
    
    std::vector<double> timeSteps(1, 1.0);
    
    CallOption call(expiry, strike);
    PutOption put(expiry, strike);
    EuropeanDigitalCallOption digitalCall(expiry,strike);
    EuropeanDigitalPutOption  digitalPut(expiry,strike);
    AsianCallOption asianCall(timeSteps, strike);
    
    BlackScholesPricer<EuropeanVanillaOption> callBS(&call, asset_price, interest_rate, volatility);
    BlackScholesPricer<EuropeanVanillaOption> putBS(&put, asset_price, interest_rate, volatility);
    BlackScholesPricer<EuropeanDigitalOption> digitalCallBS(&digitalCall, asset_price, interest_rate, volatility);
    BlackScholesPricer<EuropeanDigitalOption> digitalPutBS(&digitalPut, asset_price, interest_rate, volatility);
    BlackScholesMCPricer<AsianCallOption>  BsMcCall(&asianCall, asset_price, interest_rate,volatility);
    
    BsMcCall.generate(10000000);
    
    std::cout<< "call price BS " << callBS()<< std::endl;
    std::cout<< "call delta BS " << callBS.Delta()<< std::endl;
    std::cout<< "call BS MC path number " << BsMcCall.getNbPaths()<< std::endl;
    std::cout<< "call BS MC " << BsMcCall()<< std::endl;
    std::cout<< "call BS MC Confidence Interval lower bound " <<
    std::fixed << std::setprecision(10)<<
    BsMcCall.confidenceInterval()[0]<< std::endl;
    
    std::cout<< "call BS MC Confidence Interval upper bound " << BsMcCall.confidenceInterval()[1]<< std::endl;
    
    std::cout<< "put price BS " << putBS()<< std::endl;
    std::cout<< "put delta BS " << putBS.Delta()<< std::endl;
    
    std::cout<< "digital call price BS " << digitalCallBS()<< std::endl;
    std::cout<< "digital call delta BS " << digitalCallBS.Delta()<< std::endl;
    
    std::cout<< "digital put price BS " << digitalPutBS()<< std::endl;
    std::cout<< "digital put delta BS " << digitalPutBS.Delta()<< std::endl;
    
    CRRPricer pricerCallCRR(&call, depth,asset_price, up,down, R);
    CRRPricer pricerPutCRR(&put, depth,asset_price, up,down, R);
    CRRPricer pricerDigitalCallCRR(&digitalCall, depth,asset_price, up,down, R);
    CRRPricer pricerDigitalPutCRR(&digitalPut, depth,asset_price, up,down, R);

    std::cout<< "call price CRR closed form " << pricerCallCRR(true)<< std::endl;
    std::cout<< "call price CRR procedure " << pricerCallCRR()<< std::endl;

    std::cout<< "put price CRR closed form " << pricerPutCRR(true)<< std::endl;
    std::cout<< "put price CRR procedure " << pricerPutCRR()<< std::endl;

    std::cout<< "digital call price CRR closed form " << pricerDigitalCallCRR(true)<< std::endl;
    std::cout<< "digital call price CRR procedure " << pricerDigitalCallCRR()<< std::endl;

    std::cout<< "digital put price CRR closed form " << pricerDigitalPutCRR(true)<< std::endl;
    std::cout<< "digital put price CRR procedure " << pricerDigitalPutCRR()<< std::endl;

    return 0;

}
 */
