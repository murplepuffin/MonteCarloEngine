#include "pricing/EuropeanPayoffs.hpp"
#include "pricing/MonteCarloPricer.hpp"
#include "random/BoxMullerNormal.hpp"
#include "random/MTRandom.hpp"

#include <iostream>
#include <memory>

int main() {
    auto normalGenerator = std::make_unique<BoxMullerNormal>(
        std::make_unique<MTRandom>(42));
    MonteCarloPricer pricer(std::move(normalGenerator));

    const BlackScholesModel model{
        .spot = 100.0,
        .riskFreeRate = 0.05,
        .volatility = 0.2,
        .maturity = 1.0,
    };
    EuropeanCallPayoff call(100.0);

    std::cout << "European call price: "
              << pricer.priceEuropean(call, model, 1'000'000) << '\n';
    return 0;
}
