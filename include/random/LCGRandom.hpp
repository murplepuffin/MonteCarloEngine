#pragma once

#include "IRandomGenerator.hpp"
#include <cstdint>

class LCGRandom : public IRandomGenerator {
private:
    uint64_t state;

    static constexpr uint64_t a = 1664525;
    static constexpr uint64_t c = 1013904223;
    static constexpr uint64_t m = (1ULL << 32);

public:
    explicit LCGRandom(uint64_t seed);

    double nextDouble() override;
};
