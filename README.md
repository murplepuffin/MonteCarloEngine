# Monte Carlo Engine

A small C++ library of random-number generators for Monte Carlo simulations.

## Build and run

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
./build/monte_carlo_demo
```

## Test

```sh
ctest --test-dir build --output-on-failure
```

GitHub Actions runs the same build and test commands on pushes and pull requests.
