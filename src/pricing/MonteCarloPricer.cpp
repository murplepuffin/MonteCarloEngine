#include "pricing/MonteCarloPricer.hpp"

#include <cmath>
#include <stdexcept>
#include <utility>

MonteCarloPricer::MonteCarloPricer(
    std::unique_ptr<INormalGenerator> normalGenerator)
    : normalGenerator_(std::move(normalGenerator)) {
    if (!normalGenerator_) {
        throw std::invalid_argument("A normal generator is required");
    }
}

double MonteCarloPricer::priceEuropean(const Payoff& payoff,
                                       const BlackScholesModel& model,
                                       std::size_t paths) {
    if (model.spot < 0.0 || model.volatility < 0.0 || model.maturity < 0.0) {
        throw std::invalid_argument(
            "Spot, volatility, and maturity must be non-negative");
    }
    if (paths == 0) {
        throw std::invalid_argument("At least one simulation path is required");
    }

    const double drift =
        (model.riskFreeRate - 0.5 * model.volatility * model.volatility)
        * model.maturity;
    const double diffusion = model.volatility * std::sqrt(model.maturity);

    double payoffSum = 0.0;
    for (std::size_t path = 0; path < paths; ++path) {
        const double terminalSpot = model.spot * std::exp(
            drift + diffusion * normalGenerator_->nextNormal());
        payoffSum += payoff(terminalSpot);
    }

    return std::exp(-model.riskFreeRate * model.maturity)
           * payoffSum / static_cast<double>(paths);
}
