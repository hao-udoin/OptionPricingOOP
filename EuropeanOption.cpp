#include <cmath>
#include <vector>
#include <iostream>
#include <iomanip>

using namespace std;

#include "EuropeanOption.h"

EuropeanOption::EuropeanOption(bool isCall, double s, double k, double t, double sigma, double r, double q)
    : OptionBase(isCall,s, k, t, sigma, r, q) {}

double normalCDF(double x) {
    return std::erfc(-x/std::sqrt(2)) / 2;
}

double EuropeanOption::priceBlackScholes() {
    double d1 = (std::log(s / k) + (r - q + 0.5 * std::pow(sigma, 2)) * t) / (sigma * std::sqrt(t));
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
    double u = std::exp(sigma * std::sqrt(dt));
    double d = 1 / u;
    double p_u = (std::exp((r-q)*dt) - d) / (u-d);
    double p_d = 1 - p_u;

    std::cout << "u: " << std::fixed << std::setprecision(2) << u 
              << " d: " << d << " p_u: " << p_u << " p_d: " << p_d << std::endl;

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
    for (int j = n_steps; j >= 1; --j) {
        // at each step, update binomialValues at each level
        for (int i = 0; i < j; ++i) {
            binomialValues[i] = p_u * binomialValues[i] + (p_d) * binomialValues[i+1];
            // discount by rates given
            binomialValues[i] *= std::exp((q-r) * dt);
        }
    }

    // return the option price at the root of the tree
    return binomialValues[0];
}

double EuropeanOption::priceTrinomialTree(int n_steps) {
    double dt = t / n_steps;

    // volatility matching as by CRR
    double u = std::exp(sigma * std::sqrt(3 * dt));
    double d = 1 / u;
    double p_u = (1.0/6.0) + std::sqrt(dt / (12 * sigma*sigma)) * (r - q - sigma*sigma/2);
    double p_d = (1.0/6.0) - std::sqrt(dt / (12 * sigma*sigma)) * (r - q - sigma*sigma/2);
    double p_m  = 2.0/3.0;

    std::cout << "u: " << std::fixed << std::setprecision(2) << u 
              << " d: " << d << " p_u: " << p_u << " p_d: " << p_d << std::endl;

    // generate stock prices at terminal nodes
    std::vector<double> prices(2 * n_steps + 1);
    prices[0] = s * std::pow(u, n_steps);
    for (int i = 1; i <= 2 * n_steps; ++i) {
        prices[i] = prices[i-1] * d;
    }

    // generate option values at terminal nodes
    std::vector<double> trinomialValues(2 * n_steps + 1);
    if (isCall){
        for (int i = 0; i <= n_steps; ++i) {
            trinomialValues[i] = std::max(0.0, prices[i] - k);
        }
    } else {
        for (int i = 0; i <= n_steps; ++i) {
            trinomialValues[i] = std::max(0.0, k - prices[i]);
        }
    }

    // back step (calculate binomialValues at preceding levels) until root
    for (int j = n_steps; j >= 1; --j) {
        // at each step, update binomialValues at each level
        for (int i = 0; i < 2 * j; ++i) {
            trinomialValues[i] = p_u * trinomialValues[i] 
                                + p_m * trinomialValues[i+1] 
                                + p_d * trinomialValues[i+2];
            // discount by rates given
            trinomialValues[i] *= std::exp((q-r) * dt);
        }
    }

    // return the option price at the root of the tree
    return trinomialValues[0];
}