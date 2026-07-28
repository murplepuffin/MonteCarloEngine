# Monte Carlo Engine

A C++20 Monte Carlo pricing foundation.

## Current capabilities

- Uniform random-number generators: linear congruential and Mersenne Twister.
- Standard-normal variates through the Box--Muller transform.
- European call and put payoffs.
- Risk-neutral Monte Carlo pricing under a Black--Scholes model.

The demo prices a one-year at-the-money European call:

```sh
cmake -S . -B build
cmake --build build
./build/montecarlo
```

Run the test suite with:

```sh
ctest --test-dir build --output-on-failure
```

## Pricing API

Construct a `MonteCarloPricer` with any `INormalGenerator`, then provide a
payoff, a `BlackScholesModel`, and a number of paths. This keeps payoff logic,
market assumptions, and random-number generation independently replaceable.
