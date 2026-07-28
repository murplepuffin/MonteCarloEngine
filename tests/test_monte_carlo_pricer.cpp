#include <gtest/gtest.h>

#include "pricing/EuropeanPayoffs.hpp"
#include "pricing/MonteCarloPricer.hpp"
#include "random/BoxMullerNormal.hpp"
#include "random/MTRandom.hpp"

#include <cmath>
#include <memory>
#include <stdexcept>

namespace {

std::unique_ptr<INormalGenerator> makeNormalGenerator(unsigned int seed) {
    return std::make_unique<BoxMullerNormal>(
        std::make_unique<MTRandom>(seed));
}

}  // namespace

TEST(EuropeanPayoffTest, CallAndPutReturnIntrinsicValue) {
    EuropeanCallPayoff call(100.0);
    EuropeanPutPayoff put(100.0);

    EXPECT_DOUBLE_EQ(call(120.0), 20.0);
    EXPECT_DOUBLE_EQ(call(80.0), 0.0);
    EXPECT_DOUBLE_EQ(put(80.0), 20.0);
    EXPECT_DOUBLE_EQ(put(120.0), 0.0);
}

TEST(MonteCarloPricerTest, ZeroVolatilityMatchesDiscountedPayoff) {
    MonteCarloPricer pricer(makeNormalGenerator(42));
    EuropeanCallPayoff call(90.0);
    const BlackScholesModel model{
        .spot = 100.0,
        .riskFreeRate = 0.05,
        .volatility = 0.0,
        .maturity = 1.0,
    };

    EXPECT_NEAR(pricer.priceEuropean(call, model, 10),
                100.0 - 90.0 * std::exp(-0.05),
                1e-12);
}

TEST(MonteCarloPricerTest, PricesEuropeanCallNearBlackScholesValue) {
    MonteCarloPricer pricer(makeNormalGenerator(42));
    EuropeanCallPayoff call(100.0);
    const BlackScholesModel model{
        .spot = 100.0,
        .riskFreeRate = 0.05,
        .volatility = 0.2,
        .maturity = 1.0,
    };

    EXPECT_NEAR(pricer.priceEuropean(call, model, 200000), 10.4506, 0.15);
}

TEST(MonteCarloPricerTest, RejectsInvalidInputs) {
    MonteCarloPricer pricer(makeNormalGenerator(42));
    EuropeanCallPayoff call(100.0);
    const BlackScholesModel invalidModel{
        .spot = 100.0,
        .riskFreeRate = 0.05,
        .volatility = -0.2,
        .maturity = 1.0,
    };

    EXPECT_THROW(pricer.priceEuropean(call, invalidModel, 1000), std::invalid_argument);
    EXPECT_THROW(pricer.priceEuropean(call, BlackScholesModel{100.0, 0.05, 0.2, 1.0}, 0),
                 std::invalid_argument);
}
