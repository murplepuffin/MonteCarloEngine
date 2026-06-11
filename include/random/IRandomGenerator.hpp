#pragma once

class IRandomGenerator {
public:
    virtual ~IRandomGenerator() = default;

    virtual double nextDouble() = 0;
};
