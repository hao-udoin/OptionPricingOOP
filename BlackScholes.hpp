#ifndef BLACK_SCHOLES_HPP
#define BLACK_SCHOLES_HPP

#include <cmath>
#include <boost/math/distributions/normal.hpp>

class BlackScholes {
private:
    double strikePrice;
    double maturity;
    double riskFreeRate;
    double volatility;
    bool isCall;

public:
    BlackScholes(double strike, double exp, double rate, double vol, bool call)
        : strikePrice(strike), maturity(exp), riskFreeRate(rate), volatility(vol), isCall(call) {}

    double calcD1(double spotPrice) const {
        return (std::log(spotPrice / strikePrice) + (riskFreeRate + 0.5 * volatility * volatility) * maturity) / (volatility * std::sqrt(maturity));
    }

    double calcD2(double d1) const {
        return d1 - volatility * std::sqrt(maturity);
    }

    double price(double spotPrice) const {
        boost::math::normal_distribution<> normal(0.0, 1.0);
        double d1 = calcD1(spotPrice);
        double d2 = calcD2(d1);

        if (isCall) {
            return spotPrice * boost::math::cdf(normal, d1) - strikePrice * std::exp(-riskFreeRate * maturity) * boost::math::cdf(normal, d2);
        } else {
            return strikePrice * std::exp(-riskFreeRate * maturity) * boost::math::cdf(normal, -d2) - spotPrice * boost::math::cdf(normal, -d1);
        }
    }
};

#endif // BLACK_SCHOLES_HPP
