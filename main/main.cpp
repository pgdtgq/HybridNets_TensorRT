#include <iostream>
#include <memory>
#include "HybridNets.h"

using namespace std;

int main() {
    auto hybridnets = std::make_shared<HybridNets>();
    hybridnets->run();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
