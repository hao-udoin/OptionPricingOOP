#include <cmath>
#include <vector>

#include "EuropeanOption.h"

EuropeanOption::EuropeanOption(bool isCall, double s, double k, double t, double sigma, double r, double q)
    : OptionBase(isCall,s, k, t, sigma, r, q) {}

double normalCDF(double x) {
    return erfc(-x/sqrt(2)) / 2;
}

double EuropeanOption::priceBlackScholes() {
    double d1 = log(s/k) + (r - q + pow(sigma, 2)/2) * t;
    double d2 = d1 - sigma * sqrt(t);

    double price;
    if (isCall) {
        price = s * exp(-q*t) * normalCDF(d1) - k * exp(-r*t) * normalCDF(d2);
    } else {
        price = - s * exp(-q*t) * normalCDF(-d1) + k * exp(-r*t) * normalCDF(-d2);
    }
    return price;
}

double EuropeanOption::priceBinomialTree(int n_steps) {
    dt = t / n_steps;

    // volatility matching as by CRR
    double u = exp(-sigma / sqrt(dt));
    double d = 1 / u;
    double p = (exp((r-q)*dt) - d) / (u-d);

    // generate final prices
    std::vector<double> prices(n_steps + 1);
    prices[0] = s * pow(u, i)
    for (int i = 0; i <= steps; ++i) {
        prices[i] = 
    }
}