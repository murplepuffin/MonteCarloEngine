#pragma once

class INormalGenerator {
public:
    virtual ~INormalGenerator() = default;

    virtual double nextNormal() = 0;
};
