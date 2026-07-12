cmake_minimum_required(VERSION 3.16)

project(MonteCarloEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(monte_carlo_engine
    src/random/BoxMullerNormal.cpp
    src/random/LCGRandom.cpp
    src/random/MTRandom.cpp
)

target_include_directories(monte_carlo_engine PUBLIC include)

add_executable(monte_carlo_demo main.cpp)
target_link_libraries(monte_carlo_demo PRIVATE monte_carlo_engine)

include(CTest)
if(BUILD_TESTING)
    add_executable(random_generators_test tests/random_generators_test.cpp)
    target_link_libraries(random_generators_test PRIVATE monte_carlo_engine)
    add_test(NAME random_generators COMMAND random_generators_test)
endif()
