#include <gtest/gtest.h>

#include "random/BoxMullerNormal.hpp"
#include "random/MTRandom.hpp"

TEST(BoxMullerTest, DistributionStatistics) {

    auto rng = std::make_unique<MTRandom>(42);

    BoxMullerNormal normal(std::move(rng));

    const int N = 1000000;

    double sum = 0.0;
    double sumSq = 0.0;

    for (int i = 0; i < N; ++i) {

        double x = normal.nextNormal();

        sum += x;
        sumSq += x * x;
    }

    double mean = sum / N;

    double variance =
        (sumSq / N) - (mean * mean);

    EXPECT_NEAR(mean, 0.0, 0.01);
    EXPECT_NEAR(variance, 1.0, 0.02);
}
