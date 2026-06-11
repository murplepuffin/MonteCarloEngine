#include <gtest/gtest.h>

#include "random/LCGRandom.hpp"

TEST(LCGRandomTest, ValuesAreInRange) {
    LCGRandom rng(42);

    for (int i = 0; i < 100000; ++i) {
        double value = rng.nextDouble();

        EXPECT_GE(value, 0.0);
        EXPECT_LT(value, 1.0);
    }
}

TEST(LCGRandomTest, SameSeedProducesSameSequence) {
    LCGRandom rng1(12345);
    LCGRandom rng2(12345);

    for (int i = 0; i < 1000; ++i) {
        EXPECT_DOUBLE_EQ(
            rng1.nextDouble(),
            rng2.nextDouble()
        );
    }
}

TEST(LCGRandomTest, MeanIsApproximatelyHalf) {
    LCGRandom rng(42);

    const int N = 1000000;

    double sum = 0.0;

    for (int i = 0; i < N; ++i) {
        sum += rng.nextDouble();
    }

    double mean = sum / N;

    EXPECT_NEAR(mean, 0.5, 0.01);
}
