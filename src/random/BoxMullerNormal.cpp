#include "random/BoxMullerNormal.hpp"

#include <algorithm>
#include <cmath>
#include <limits>

BoxMullerNormal::BoxMullerNormal(
    std::unique_ptr<IRandomGenerator> rng)
    : uniformRng(std::move(rng)) {}

double BoxMullerNormal::nextNormal() {

    const double u1 = std::max(
        uniformRng->nextDouble(),
        std::numeric_limits<double>::min());
    double u2 = uniformRng->nextDouble();

    return std::sqrt(-2.0 * std::log(u1))
           * std::cos(2.0 * std::acos(-1.0) * u2);
}
