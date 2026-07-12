#include "random/BoxMullerNormal.hpp"
#include "random/LCGRandom.hpp"
#include "random/MTRandom.hpp"

#include <cassert>
#include <cmath>
#include <memory>

namespace {

class ConstantRandom final : public IRandomGenerator {
public:
    explicit ConstantRandom(double value) : value_(value) {}

    double nextDouble() override { return value_; }

private:
    double value_;
};

void expectUnitInterval(IRandomGenerator& generator) {
    for (int i = 0; i < 1'000; ++i) {
        const double value = generator.nextDouble();
        assert(value >= 0.0);
        assert(value < 1.0);
    }
}

} // namespace

int main() {
    LCGRandom lcg(42);
    MTRandom mt(42);
    expectUnitInterval(lcg);
    expectUnitInterval(mt);

    BoxMullerNormal normal(std::make_unique<MTRandom>(42));
    for (int i = 0; i < 1'000; ++i) {
        assert(std::isfinite(normal.nextNormal()));
    }

    BoxMullerNormal zeroSafeNormal(std::make_unique<ConstantRandom>(0.0));
    assert(std::isfinite(zeroSafeNormal.nextNormal()));
}
