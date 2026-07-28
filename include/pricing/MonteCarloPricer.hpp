#pragma once

#include "pricing/BlackScholesModel.hpp"
#include "pricing/Payoff.hpp"
#include "random/INormalGenerator.hpp"

#include <cstddef>
#include <memory>

class MonteCarloPricer {
public:
    explicit MonteCarloPricer(std::unique_ptr<INormalGenerator> normalGenerator);

    double priceEuropean(const Payoff& payoff,
                         const BlackScholesModel& model,
                         std::size_t paths);

private:
    std::unique_ptr<INormalGenerator> normalGenerator_;
};
