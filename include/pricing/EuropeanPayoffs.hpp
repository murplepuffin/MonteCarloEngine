#pragma once

#include "pricing/Payoff.hpp"

#include <algorithm>

class EuropeanCallPayoff final : public Payoff {
public:
    explicit EuropeanCallPayoff(double strike) : strike_(strike) {}

    double operator()(double spot) const override {
        return std::max(spot - strike_, 0.0);
    }

private:
    double strike_;
};

class EuropeanPutPayoff final : public Payoff {
public:
    explicit EuropeanPutPayoff(double strike) : strike_(strike) {}

    double operator()(double spot) const override {
        return std::max(strike_ - spot, 0.0);
    }

private:
    double strike_;
};
