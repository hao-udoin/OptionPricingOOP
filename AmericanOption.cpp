#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

#include "AmericanOption.h"

AmericanOption::AmericanOption(bool isCall, double s, double k, double t, double sigma, double r, double q)
    : OptionBase(isCall,s, k, t, sigma, r, q) {}

double AmericanOption::priceBlackScholes() {
    std::cout << "Method not applicable to option type given." << std::endl;
}

double AmericanOption::priceBinomialTree(int n_steps) {
    double dt = t / n_steps;

    // volatility matching as by CRR
    double u = std::exp(-sigma / std::sqrt(dt));
    double d = 1 / u;
    double p = (std::exp((r-q)*dt) - d) / (u-d);

    std::vector<double> prices(n_steps + 1);
    prices[0] = std::pow(u, n_steps);
    for (int i = 1; i <= n_steps; ++i) {
        prices[i] = prices[i-1] * d;
    }

    std::vector<double> binomialValues(n_steps + 1);
    if (isCall) {
        for (int i = 0; i <= n_steps; ++i) {
            binomialValues[i] = std::max(0.0, prices[i] - k);
        }
    } else {
        for (int i = 0; i <= n_steps; ++i) {
            binomialValues[i] = std::max(0.0, k - prices[i]);
        }
    }

    if (isCall) {
        for (int j = n_steps; j >= 1; --j) {
            for (int i = 0; i <= j; ++i) {
                binomialValues[i] = p * binomialValues[i] + (1-p) * binomialValues[i+1];
                binomialValues[i] *= exp((q-r) * dt);
                // here it differs from European options
                binomialValues[i] = std::max(prices[i] - k, binomialValues[i]);
            }
        }     
    } else {
        for (int j = n_steps; j >= 1; --j) {
            for (int i = 0; i <= j; ++i) {
                binomialValues[i] = p * binomialValues[i] + (1-p) * binomialValues[i+1];
                binomialValues[i] *= exp((q-r) * dt);
                // here it differs from European options
                binomialValues[i] = std::max(k - prices[i], binomialValues[i]);
            }
    }
    
    return binomialValues[0];
}
