#pragma once

#include "INormalGenerator.hpp"
#include "IRandomGenerator.hpp"

#include <memory>

class BoxMullerNormal : public INormalGenerator {
private:
    std::unique_ptr<IRandomGenerator> uniformRng;

public:
    explicit BoxMullerNormal(
        std::unique_ptr<IRandomGenerator> rng
    );

    double nextNormal() override;
};
