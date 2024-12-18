#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

#include "AmericanOption.h"

AmericanOption::AmericanOption(bool isCall, double s, double k, double t, double sigma, double r, double q)
    : OptionBase(isCall,s, k, t, sigma, r, q) {}

void AmericanOption::priceBlackScholes() {
    std::cout << "Method not applicable to option type given." << std::endl;
}

double AmericanOption::priceBinomialTree(int n_steps) {
    double dt = t / n_steps;

    // volatility matching as by CRR
    double u = std::exp(sigma * std::sqrt(dt));
    double d = 1 / u;
    double p = (std::exp((r-q)*dt) - d) / (u-d);

    std::cout << "u: " << std::fixed << std::setprecision(2) << u 
              << " d: " << d << " p: " << p << std::endl;

    // generate stock prices at terminal nodes
    std::vector<double> prices(n_steps + 1);
    prices[0] = s * std::pow(u, n_steps);
    for (int i = 1; i <= n_steps; ++i) {
        prices[i] = prices[i-1] * d * d;
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
    if (isCall) {
        for (int j = n_steps; j >= 1; --j) {
            std::cout << "Step " << j << " prices: ";
            for (int i = 0; i <= j; ++i) {
                binomialValues[i] = p * binomialValues[i] + (1-p) * binomialValues[i+1];
                binomialValues[i] *= std::exp((q-r) * dt);
                // here it differs from European options
                prices[i] *= d;
                binomialValues[i] = std::max(prices[i] - k, binomialValues[i]);
                std::cout << std::fixed << std::setprecision(2) << binomialValues[i] << " ";
            }
            std::cout << std::endl;
        }     
    } else {
        for (int j = n_steps; j >= 1; --j) {
            std::cout << "Step " << j << " prices: ";
            for (int i = 0; i <= j; ++i) {
                binomialValues[i] = p * binomialValues[i] + (1-p) * binomialValues[i+1];
                binomialValues[i] *= std::exp((q-r) * dt);
                // here it differs from European options
                prices[i] *= d;
                binomialValues[i] = std::max(k - prices[i], binomialValues[i]);
                std::cout << std::fixed << std::setprecision(2) << binomialValues[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    // return the option price at the root of the tree
    return binomialValues[0];
};
