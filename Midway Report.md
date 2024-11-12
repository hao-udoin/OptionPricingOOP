
Midway Report for Option Pricing Project 
=

Project Overview
-

The goal of this project is to develop a flexible and extensible C++ program for option pricing. Currently, the focus is on implementing the Binomial Tree model as a foundation, but the project is designed to accommodate other models in the future. This project aims to provide a robust framework for option pricing that can be expanded to handle various option types and pricing methodologies.


The project is now divided into two main components:

1.  **Option Class**: This class contains the basic properties of an option, such as strike price, maturity, risk-free interest rate, volatility, and option type (call or put).
2.  **Binomial Tree Class**: This class implements the Binomial Tree model to calculate the price of the option by building a price tree and back-propagating the option values.

Project Structure
-----------------

The project consists of two main files:

1.  `Option.hpp`: This header file contains the definitions and implementations of the `Option` and `BinomialTree` classes.
2.  `main.cpp`: This file contains the main function to test and demonstrate the functionality of the `Option` and `BinomialTree` classes.

### Option Class

The `Option` class is designed to represent the essential attributes of an option. It includes the following members:

-   **Attributes**:
    
    -   `strikePrice`: The price at which the option can be exercised.
    -   `maturity`: The time until the option's expiration, in years.
    -   `riskFreeRate`: The risk-free interest rate used to discount future cash flows.
    -   `volatility`: The volatility of the underlying asset's price.
    -   `isCall`: A boolean that indicates whether the option is a call (true) or put (false).


### Binomial Tree Class

The `BinomialTree` class is responsible for calculating the price of a European option using the Binomial Tree model. It creates a tree structure for the underlying asset price and uses a backward induction method to calculate the option price.

-   **Methods**:
    -   `price(const Option& option, int steps)`: This method takes an `Option` object and the number of steps in the binomial tree. It builds the binomial tree and calculates the option’s value by working backward from the terminal nodes to the root.
        
    -   **Implementation Steps**:
        
        1.  **Parameter Calculation**: Calculates the time step size (`deltaT`), up factor, down factor, and risk-neutral probability `p`.
        2.  **Terminal Payoffs**: Initializes the option values at the terminal nodes (maturity).
        3.  **Backward Induction**: Uses backward induction to calculate the option’s value at each node until reaching the root, which gives the option price.

Current Progress
----------------

1.  **Option Class**:
    
    -   The `Option` class has been fully implemented with constructors and getter methods.
    -   This class provides all necessary attributes to represent an option and supports both call and put options.
2.  **BinomialTree Class**:
    
    -   The `BinomialTree` class has been implemented to calculate the option price for European options.
    -   The class has been tested with basic inputs and provides correct values for European call and put options based on the Binomial Tree model.
3.  **Testing**:
    
    -   We have successfully tested the implementation with sample inputs (e.g., spot price = 100, strike price = 100, risk-free rate = 5%, volatility = 20%, time to expiry = 1 year, and 100 steps).
    -   The program outputs the option prices for both call and put options, matching expected theoretical results.


Future Work
-----------

1.  **Extending to American Options**: The next step is to adapt the `BinomialTree` class to support American options. This will involve adding a condition to allow for early exercise at each node during backward induction.
2.  **Refactoring Code for Modularity**: Splitting the code into separate `.cpp` and `.hpp` files for better modularity and readability.
3.  **Adding Black-Scholes model**: Implementing Black-sholes model as an alternative method for option pricing. 
4.  **Adding Monte Carlo Simulation**: Implementing Monte Carlo simulation as an alternative method for option pricing.
5.  **User Interface**: Developing a command-line or graphical user interface to allow users to input option parameters interactively.

Conclusion
----------

The project is progressing well, and the Binomial Tree model for European option pricing has been successfully implemented and tested. The current implementation provides accurate results and serves as a solid foundation for future extensions, including the Black-Scholes model and American option pricing. Moving forward, we aim to enhance the program’s flexibility and usability by adding additional pricing models and supporting various option types.

