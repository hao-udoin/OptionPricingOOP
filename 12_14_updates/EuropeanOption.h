#ifndef EUROPEAN_OPTION_H
#define EUROPEAN_OPTION_H

#include "OptionBase.h"

class EuropeanOption : public OptionBase {
    public:
        EuropeanOption(bool isCall, double s, double k, double t, double sigma, double r, double q);
    
        double priceBlackScholes();
        double priceBinomialTree(int n_steps);

    private:

};

#endif