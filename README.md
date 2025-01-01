# C++ for Finance - Teaching Library

**Author:** M.Hseini
**Year:** 2024

---

## Project Purpose

This C++ library is developed as part of a **C++ for Finance** course and is intended for **teaching purposes only**. It provides a practical implementation of key financial models and techniques for option pricing. The library focuses on applying object-oriented programming concepts and financial mathematics to solve real-world problems in finance.

---

## Scope of the Library

The library includes implementations of:

1. **Black-Scholes Model (Part I):**
   - Class hierarchy for European vanilla options (`CallOption` and `PutOption`).
   - Pricing options using the Black-Scholes formula.
   - Computing the Delta of options.

2. **Cox-Ross-Rubinstein (CRR) Model (Part II):**
   - Template-based `BinaryTree` class for representing binomial trees.
   - Backward induction for pricing European options.
   - Support for **Digital Options** with closed-form and numerical methods.

3. **Monte Carlo Simulations (Part III):**
   - Simulation of asset price paths using the Black-Scholes dynamics.
   - Pricing path-dependent options (e.g., Asian options) using Monte Carlo methods.
   - Confidence interval estimation for option prices.

4. **American Options in CRR (Part IV):**
   - Support for pricing American options using backward induction.
   - Early exercise policies stored in a `BinaryTree<bool>`.
   - Approximation of the Black-Scholes model using a CRR approach for large `N`.

---

## Features Included in This Version

This library implements the following core components:

1. **Option Class Hierarchy:**
   - `Option` (abstract base class).
   - `VanillaOption` (derived class) with subclasses `CallOption` and `PutOption`.
   - Support for both European and American options.

2. **BinaryTree Template Class:**
   - Representation of binomial trees for the CRR model.
   - Methods to set and retrieve node values, display the tree structure.

3. **Pricers:**
   - `BlackScholesPricer`: Analytical pricing using the Black-Scholes formula.
   - `CRRPricer`: Numerical pricing using backward induction in a binomial tree.

4. **Monte Carlo Simulation:**
   - `BlackScholesMCPricer`: Simulates asset price paths to estimate option prices.
   - Confidence interval calculation for Monte Carlo estimates.

5. **Digital Options:**
   - `DigitalCallOption` and `DigitalPutOption` for digital options pricing.

6. **American Options in CRR:**
   - Early exercise policies for American options.
   - Integration with `CRRPricer`.

7. **Singleton Random Number Generator:**
   - `MT` class for consistent random number generation (`std::mt19937`).

---

## Key Notes for Users

- **Educational Use Only:** This library is designed for teaching purposes and may lack production-level robustness or optimizations.
- **Partial Implementation:** Not all features of the described project are included; focus is on foundational concepts and core implementations.
- **Main Functionality:** All implementations are designed to demonstrate theoretical models and pricing techniques.

---

## License and Disclaimer

This library is provided **as-is** for educational purposes. It is not intended for commercial use or financial decision-making. The author and contributors bear no responsibility for the correctness or accuracy of the code or models.

---

## References and Further Reading

- **Black-Scholes Model:** [Wikipedia](https://en.wikipedia.org/wiki/Black–Scholes_model)  
- **CRR Model:** [Wikipedia](https://en.wikipedia.org/wiki/Binomial_options_pricing_model)  
- **Monte Carlo Simulations:** [Wikipedia](https://en.wikipedia.org/wiki/Monte_Carlo_method)
