cmake_minimum_required(VERSION 3.16)

project(MonteCarloEngine VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ============================================
# Warnings
# ============================================

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ============================================
# Include Directories
# ============================================

include_directories(include)

# ============================================
# Main Library
# ============================================

add_library(random_lib
    src/random/LCGRandom.cpp
    src/random/MTRandom.cpp
    src/random/BoxMullerNormal.cpp
)

target_include_directories(random_lib PUBLIC include)

# ============================================
# Pricing Library
# ============================================

add_library(pricing_lib
    src/pricing/MonteCarloPricer.cpp
)

target_include_directories(pricing_lib PUBLIC include)
target_link_libraries(pricing_lib PUBLIC random_lib)

# ============================================
# Main Executable
# ============================================

add_executable(montecarlo
    main.cpp
)

target_link_libraries(montecarlo PRIVATE pricing_lib)

# ============================================
# GoogleTest
# ============================================

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# ============================================
# Test Executable
# ============================================

add_executable(random_tests
    tests/test_lcg.cpp
    tests/test_mt.cpp
    tests/test_boxmuller.cpp
    tests/test_monte_carlo_pricer.cpp
)

target_link_libraries(random_tests
    PRIVATE
    pricing_lib
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(random_tests)
