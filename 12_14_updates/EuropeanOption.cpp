#include <cmath>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

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

     // Generate terminal prices
    vector<double> prices(n_steps + 1);
    for (int i = 0; i <= n_steps; ++i) {
        prices[i] = s * pow(u, n_steps - i) * pow(d, i);
    }

    // Generate option values at terminal nodes
    vector<double> optionValues(n_steps + 1);
    for (int i = 0; i <= n_steps; ++i) {
        if (isCall) {
            optionValues[i] = max(0.0, prices[i] - k);
        } else {
            optionValues[i] = max(0.0, k - prices[i]);
        }
    }

    // Backward induction through the tree
    for (int step = n_steps - 1; step >= 0; --step) {
        for (int i = 0; i <= step; ++i) {
            double hold = exp(-r * dt) * (p * optionValues[i] + (1 - p) * optionValues[i + 1]);
            if (isAmerican) {
                double exercise;
                if (isCall) {
                    exercise = max(0.0, prices[i] - k);
                } else {
                    exercise = max(0.0, k - prices[i]);
                }
                optionValues[i] = max(hold, exercise);
            } else {
                optionValues[i] = hold;
            }
            prices[i] = prices[i] / u; // Move one step backward in the tree
        }
    }

    // Return the option price at the root of the tree
    double binomialPrice = optionValues[0];

    // Compare with Black-Scholes if European option
    if (!isAmerican) {
        double bsPrice = priceBlackScholes();
        cout << "Binomial Tree Price: " << binomialPrice << "\n";
        cout << "Black-Scholes Price: " << bsPrice << "\n";
        cout << "Difference: " << fabs(binomialPrice - bsPrice) << "\n";
    }

    return binomialPrice;
}
