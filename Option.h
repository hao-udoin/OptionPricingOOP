// Option.hpp
#ifndef OPTION_HPP
#define OPTION_HPP

#include <vector>
#include <cmath>
#include <algorithm>


class Option {
protected:
    double strikePrice;
    double maturity;
    double riskFreeRate;
    double volatility;
    bool isCall;

public:
    Option(double strike, double exp, double rate, double vol, bool call)
        : strikePrice(strike), maturity(exp), riskFreeRate(rate), volatility(vol), isCall(call) {}

    virtual ~Option() {}

    double getStrikePrice() const { return strikePrice; }
    double getMaturity() const { return maturity; }
    double getRiskFreeRate() const { return riskFreeRate; }
    double getVolatility() const { return volatility; }
    bool isCallOption() const { return isCall; }
};


class BinomialTree {
public:
    double price(const Option& option, int steps) {
        double deltaT = option.getMaturity() / steps;
        double upFactor = std::exp(option.getVolatility() * std::sqrt(deltaT));
        double downFactor = 1.0 / upFactor;
        double p = (std::exp(option.getRiskFreeRate() * deltaT) - downFactor) / (upFactor - downFactor);

        std::vector<double> optionValues(steps + 1);

        for (int i = 0; i <= steps; ++i) {
            double spotPriceAtNode = option.getStrikePrice() * std::pow(upFactor, steps - i) * std::pow(downFactor, i);
            optionValues[i] = option.isCallOption() ?
                std::max(0.0, spotPriceAtNode - option.getStrikePrice()) :
                std::max(0.0, option.getStrikePrice() - spotPriceAtNode);
        }

        for (int step = steps - 1; step >= 0; --step) {
            for (int i = 0; i <= step; ++i) {
                double spotPriceAtNode = option.getStrikePrice() * std::pow(upFactor, step - i) * std::pow(downFactor, i);
                double holdValue = (p * optionValues[i] + (1 - p) * optionValues[i + 1]) * std::exp(-option.getRiskFreeRate() * deltaT);
                double exerciseValue = option.isCallOption() ?
                    std::max(0.0, spotPriceAtNode - option.getStrikePrice()) :
                    std::max(0.0, option.getStrikePrice() - spotPriceAtNode);
                optionValues[i] = (p * optionValues[i] + (1 - p) * optionValues[i + 1])
                                  * std::exp(-option.getRiskFreeRate() * deltaT);
            }
        }

        return optionValues[0];
    }
};

#endif // OPTION_HPP
