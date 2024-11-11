// main.cpp
#include <iostream>
#include "Option.h"

int main() {
    double spotPrice = 100.0;
    double strikePrice = 100.0;
    double expiry = 1.0;          // 一年
    double riskFreeRate = 0.05;   // 5%
    double volatility = 0.2;      // 20%
    int steps = 100;              // 時間步驟數

    Option callOption(strikePrice, expiry, riskFreeRate, volatility, true);
    BinomialTree tree;
    double callPrice = tree.price(callOption, steps);

    std::cout << "European Call Option Price (Binomial Tree): " << callPrice << std::endl;

    return 0;
}