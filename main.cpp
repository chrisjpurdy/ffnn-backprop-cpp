#include <iostream>
#include "src/FFNetwork.hpp"
#include "src/DatasetStore.hpp"

int main() {

    std::srand(time(nullptr));

    auto ds = DatasetStore("../datasets/train-labels-idx1-ubyte", "../datasets/train-images-idx3-ubyte");

    std::cout << ds.getLabel(10005) << std::endl;
    DatasetStore::showDigit(ds.getDigit(10005).data());

    FFNetwork& network = (*FFNetwork::generateNetwork({28 * 28, 100, 24, 1}, {RELU, RELU, RELU}));

    network.setInputLayer(ds.getDigit(10005));
    std::cout << "Output: " << network.calculateOutputLayer()[0] << std::endl;

//    std::cout << "Network input layer: " << std::endl;
//    for (Node* node : network[0]) {
//        std::cout << node->calculateOutput() << std::endl;
//    }
//
//    std::cout << "Network output layer: " << std::endl;
//    for (auto out : network.calculateOutputLayer()) {
//        std::cout << out << std::endl;
//    }
    return 0;
}