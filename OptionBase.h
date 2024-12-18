#ifndef OPTION_BASE_H
#define OPTION_BASE_H

class OptionBase {
    protected:
        bool isCall; // true for call, false for put
        double s; // the current underlying price
        double k; // the strike price
        double t; // the time to expiration (in years)
        double sigma; // the volatility of the stock price (per annum)
        double r; // the risk-free interest rate (per annum)
        double q; // the rate of dividend yield (assumed continuous, per annum)
    
    public:
        OptionBase(bool isCall, double s, double k, double t, double sigma, double r, double q)
            : isCall(isCall), s(s), k(k), t(t), sigma(sigma), r(r), q(q) {}
        
        virtual ~OptionBase() {}
        
        /*
        virtual double price() const = 0;
        virtual double delta();
        virtual double gamma();
        virtual double theta();
        virtual double vega();
        */
};
#endif
