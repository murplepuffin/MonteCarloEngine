#include "random/BoxMullerNormal.hpp"

#include <cmath>

BoxMullerNormal::BoxMullerNormal(
    std::unique_ptr<IRandomGenerator> rng)
    : uniformRng(std::move(rng)) {}

double BoxMullerNormal::nextNormal() {

    double u1 = uniformRng->nextDouble();
    double u2 = uniformRng->nextDouble();

    return std::sqrt(-2.0 * std::log(u1))
           * std::cos(2.0 * M_PI * u2);
}
