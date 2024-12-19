#ifndef AMERICAN_OPTION_H
#define AMERICAN_OPTION_H

#include "OptionBase.h"

class AmericanOption : public OptionBase {
    public:
        AmericanOption(bool isCall, double s, double k, double t, double sigma, double r, double q);
    
        void priceBlackScholes();
        double priceBinomialTree(int n_steps);
        double priceTrinomialTree(int n_steps);
        double payoff(double underlying);

    private:

};

#endif