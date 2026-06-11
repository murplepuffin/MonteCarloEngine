#include "random/MTRandom.hpp"

MTRandom::MTRandom(uint32_t seed)
    : engine(seed),
      distribution(0.0, 1.0) {}

double MTRandom::nextDouble() {
    return distribution(engine);
}
