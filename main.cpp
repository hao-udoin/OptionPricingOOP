// main.cpp
#include <iostream>
#include "Option.h"

int main() {
    double spotPrice = 100.0;
    double strikePrice = 100.0;
    double maturity = 1.0;          
    double riskFreeRate = 0.05;  
    double volatility = 0.2;      
    int steps = 100;              

    Option callOption(strikePrice, maturity, riskFreeRate, volatility, true);
    BinomialTree tree;
    double price = tree.price(callOption, steps);

    std::cout << "European Option Price (Binomial Tree): " << price << std::endl;

    return 0;
}
