## Project Overview

This project focuses on implementing option pricing models for European-style and American-style call and put options. Using object-oriented programming principles, the project builds a modular framework to calculate option prices via three primary methods:

* Black-Scholes Formula: An analytical method for option pricing.
* Binomial Tree Method: A numerical method that approximates option prices through iterative calculations.
* Trinomial Tree Method: An extension of the binomial tree method accounting for the scenario that the price remains unchanged in dt.

The implementation includes a base class (`OptionBase`) and a derived class (`EuropeanOption`,`AmericanOption`) that extends functionality for options. The project highlights the accuracy of results, numerical stability, and the flexibility to extend the framework for other option types.

## Code Overview

### OptionBase.h

The `OptionBase` class serves as the base class for option pricing. It encapsulates common attributes required for option pricing:

Attributes:
* `bool isCall`: Indicates if the option is a call (true) or put (false).
* `double s`: Current underlying price.
* `double k`: Strike price.
* `double t`: Time to expiration (in years).
* `double sigma`: Volatility of the stock price (per annum).
* `double r`: Risk-free interest rate (per annum).
* `double q`: Dividend yield rate (continuous, per annum).

Constructor: Initializes the attributes using a parameterized constructor.

Virtual Destructor: Ensures proper cleanup in derived classes.

### EuropeanOption.h

The `EuropeanOption` class inherits from `OptionBase` and provides specific implementations for pricing European call and put options using:

Methods:
* `priceBlackScholes()`: Implements the Black-Scholes formula.
* `priceBinomialTree(int n_steps)`: Implements a binomial tree for pricing.
* `priceTrinomialTree(int n_steps)`: Implements a btrinomial tree for pricing.

### EuropeanOption.cpp

This file implements the methods declared in `EuropeanOption.h`:

`priceBlackScholes()`:

* Uses the Black-Scholes formula to calculate the option price.
* Includes calculations for d1 and d2 and uses the cumulative distribution function (normalCDF).

`priceBinomialTree(int n_steps)`:
* Divides the time to expiration into n_steps.
* Generates stock prices at terminal nodes and calculates option values using a backward induction algorithm.
* Accounts for the up (u), down (d), and risk-neutral probability (p).

Helper Function:
* normalCDF(double x): Computes the cumulative distribution function for the normal distribution.

### AmericanOption.h

The `AmericanOption` class inherits from `OptionBase` and provides specific implementations for pricing American call and put options using:

Methods:
* `priceBlackScholes()`: Implements the Black-Scholes formula.
* `priceBinomialTree(int n_steps)`: Implements a binomial tree for pricing.

### AmericanOption.cpp

This file implements the methods declared in `AmericanOption.h`:

`priceBlackScholes()`:

* This methods states that the Black-Scholes model cannot be applied to American option, because the model does not account for early exercise of American options.

`priceBinomialTree(int n_steps)`:
* Divides the time to expiration into n_steps.
* Generates stock prices at terminal nodes and calculates option values using a backward induction algorithm.
* Accounts for the up (u), down (d), and risk-neutral probability (p).
* Incorporates early exercise, which distinguishes it from the European option pricing model. 

## Challenges Faced
Precision in Numerical Methods:
* Ensuring accuracy in the Black-Scholes formula and binomial tree calculations was critical.
* Differences in results due to the number of steps in the binomial tree required thorough testing.

Implementation of Binomial Tree: 
* Designing the backward induction algorithm to handle both call and put options was challenging but successfully achieved.

Code Optimization:
* Balancing readability and performance was necessary for maintaining clean and efficient code.

## Conclusion
