#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

#include "EuropeanOption.h"

EuropeanOption::EuropeanOption(bool isCall, double s, double k, double t, double sigma, double r, double q)
    : OptionBase(isCall,s, k, t, sigma, r, q) {}

double normalCDF(double x) {
    return std::erfc(-x/sqrt(2)) / 2;
}

double EuropeanOption::priceBlackScholes() {
    double d1 = std::log(s/k) + (r - q + std::pow(sigma, 2)/2) * t;
    double d2 = d1 - sigma * std::sqrt(t);

    double price;
    if (isCall) {
        price = s * std::exp(-q*t) * normalCDF(d1) - k * std::exp(-r*t) * normalCDF(d2);
    } else {
        price = - s * std::exp(-q*t) * normalCDF(-d1) + k * std::exp(-r*t) * normalCDF(-d2);
    }
    return price;
}

double EuropeanOption::priceBinomialTree(int n_steps) {
    double dt = t / n_steps;

    // volatility matching as by CRR
    double u = std::exp(-sigma / sqrt(dt));
    double d = 1 / u;
    double p = (std::exp((r-q)*dt) - d) / (u-d);

     // generate stock prices at terminal nodes
    std::vector<double> prices(n_steps + 1);
    prices[0] = std::pow(u, n_steps);
    for (int i = 1; i <= n_steps; ++i) {
        prices[i] = prices[i-1] * d;
    }

    // generate option values at terminal nodes
    std::vector<double> binomialValues(n_steps + 1);
    if (isCall){
        for (int i = 0; i <= n_steps; ++i) {
            binomialValues[i] = std::max(0.0, prices[i] - k);
        }
    } else {
        for (int i = 0; i <= n_steps; ++i) {
            binomialValues[i] = std::max(0.0, k - prices[i]);
        }
    }

    // back step (calculate binomialValues at preceding levels) until root
    for (int j = n_steps; j >= 1; --j) {
        // at each step, update binomialValues at each level
        for (int i = 0; i <= j; ++i) {
            binomialValues[i] = p * binomialValues[i] + (1-p) * binomialValues[i+1];
            // discount by rates given
            binomialValues[i] *= std::exp((q-r) * dt);
        }
    }

    // return the option price at the root of the tree
    return binomialValues[0];
}
