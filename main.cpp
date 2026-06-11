#include <iostream>
#include "random/LCGRandom.hpp"
#include "random/MTRandom.hpp"

int main() {
    //LCGRandom rng(42);
    MTRandom rng(42);   

/* 
    for (int i = 0; i < 10; ++i) {
        std::cout << "LCG: " << rng.nextDouble() << std::endl;
    }
*/
    for (int i = 0; i < 10; i++) {
        std::cout << "MT: " << rng.nextDouble() << std::endl;
    }

/*    for (int i = 0; i < 20; ++i) {
        std::cout << normal.nextNormal() << std::endl;
    }*/

    return 0;
}
