#pragma once

#include "IRandomGenerator.hpp"
#include <random>

class MTRandom : public IRandomGenerator {
private:
    std::mt19937 engine;
    std::uniform_real_distribution<double> distribution;

public:
    explicit MTRandom(uint32_t seed);

    double nextDouble() override;
};
