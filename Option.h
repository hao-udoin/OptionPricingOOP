// Option.hpp
#ifndef OPTION_HPP
#define OPTION_HPP

#include <vector>
#include <cmath>
#include <algorithm>

// �w�q Option ���O
class Option {
protected:
    double strikePrice;
    double expiry;
    double riskFreeRate;
    double volatility;
    bool isCall;

public:
    Option(double strike, double exp, double rate, double vol, bool call)
        : strikePrice(strike), expiry(exp), riskFreeRate(rate), volatility(vol), isCall(call) {}

    virtual ~Option() {}

    double getStrikePrice() const { return strikePrice; }
    double getExpiry() const { return expiry; }
    double getRiskFreeRate() const { return riskFreeRate; }
    double getVolatility() const { return volatility; }
    bool isCallOption() const { return isCall; }
};

// �w�q BinomialTree ���O
class BinomialTree {
public:
    double price(const Option& option, int steps) {
        double deltaT = option.getExpiry() / steps;
        double upFactor = std::exp(option.getVolatility() * std::sqrt(deltaT));
        double downFactor = 1.0 / upFactor;
        double p = (std::exp(option.getRiskFreeRate() * deltaT) - downFactor) / (upFactor - downFactor);

        std::vector<double> optionValues(steps + 1);

        // �p��׺ݸ`�I������v����
        for (int i = 0; i <= steps; ++i) {
            double spotPriceAtNode = option.getStrikePrice() * std::pow(upFactor, steps - i) * std::pow(downFactor, i);
            optionValues[i] = option.isCallOption() ?
                std::max(0.0, spotPriceAtNode - option.getStrikePrice()) :
                std::max(0.0, option.getStrikePrice() - spotPriceAtNode);
        }

        // �^���p��C�Ӹ`�I������v����
        for (int step = steps - 1; step >= 0; --step) {
            for (int i = 0; i <= step; ++i) {
                optionValues[i] = (p * optionValues[i] + (1 - p) * optionValues[i + 1])
                                  * std::exp(-option.getRiskFreeRate() * deltaT);
            }
        }

        return optionValues[0];
    }
};

#endif // OPTION_HPP
