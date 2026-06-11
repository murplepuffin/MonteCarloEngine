#include "random/LCGRandom.hpp"

LCGRandom::LCGRandom(uint64_t seed)
    : state(seed) {}

double LCGRandom::nextDouble() {
    state = (a * state + c) % m;

    return static_cast<double>(state) / static_cast<double>(m);
}
