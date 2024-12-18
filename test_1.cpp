#include <iostream>
#include <vector>
#include <cmath>

#include "EuropeanOption.h"
#include "AmericanOption.h"

void testOptionPricing() {
    // Option parameters
    double S = 100.0;  // Current stock price
    double K = 100.0;  // Strike price
    double T = 1.0;    // Time to expiration (in years)
    double r = 0.05;   // Risk-free rate
    double sigma = 0.2; // Volatility
    double q = 0;   // Dividend yield

    // Create European and American options
    EuropeanOption euroCall(true, S, K, T, sigma, r, q);
    AmericanOption amerCall(true, S, K, T, sigma, r, q);

    // Price European option using Black-Scholes
    double bsPrice = euroCall.priceBlackScholes();
    std::cout << "European Call (Black-Scholes): " << std::endl;
    std::cout << "Price: " << bsPrice << std::endl;
    std::cout << std::endl;

    // Price European option using binomial tree with increasing steps
    std::vector<int> steps = {1, 2, 5, 10};
    for (int n : steps) {
        std::cout << "European Call (Binomial Tree, " << n << " steps): " << std::endl;
        double binomialPrice = euroCall.priceBinomialTree(n);
        std::cout << "Price: " << binomialPrice << std::endl;
        std::cout << std::endl;
    }

    // Price American option using binomial tree with increasing steps
    for (int n : steps) {
        std::cout << "American Call (Binomial Tree, " << n << " steps): " << std::endl;
        double binomialPrice = amerCall.priceBinomialTree(n);
        std::cout << "Price: " << binomialPrice << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    testOptionPricing();
    return 0;
}
