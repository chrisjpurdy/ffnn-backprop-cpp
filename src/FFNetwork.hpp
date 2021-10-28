//
// Created by Chris Purdy on 23/10/2021.
//

#ifndef BACKPROP_FFNETWORK_HPP
#define BACKPROP_FFNETWORK_HPP

#include <vector>
#include <random>
#include "Node.hpp"

#define E 2.71828
#define DOUBLE_MAX_BIAS 10
#define DOUBLE_MAX_WEIGHT 50
#define MAX_VALUE 255

enum ActivationFunction {
    SIGMOID,
    RELU,
};

class FFNetwork {
private:
    FFNetwork() = default;

    std::vector<std::vector<Node*>> layers = {};
public:

    void backpropagation(std::vector<double> input, std::vector<double> expected_output);

    static std::function<double(double)> activationFunctionMap(ActivationFunction a) {
        switch (a) {
            case SIGMOID:
                return [](double x){ return (1.0/(1.0 + pow(E, -x))); };
            case RELU:
                return [](double x){ return (x <= 0 ? 0 : x); };
            default:
                // No idea how we got here, just return id
                return [](double x){ return x; };
        }
    }

    static FFNetwork* generateNetwork(std::vector<int> layers, std::vector<ActivationFunction> activations) {
        if (layers.size() < 2) {
            std::cerr << "layers must be at least 2. Cannot create network!" << std::endl;
            return nullptr;
        }
        if (layers.size() - 1 != activations.size()) {
            std::cerr << "Must define one activation function for each layer (except the input layer). Cannot create network!" << std::endl;
            return nullptr;
        }

        auto* network = new FFNetwork();

        for (unsigned long i = 0; i < layers.size(); i++) {
            network->layers.emplace_back();

            if (layers[i] < 1) {
                std::cerr << "layer number must be at least 1. Cannot create network!" << std::endl;
                delete network;
                return nullptr;
            }

            for (int j = 0; j < layers[i]; j++) {
                if (i == 0) {
                    network->layers[i].emplace_back(new InputNode());
                    ((InputNode*) network->layers[i][j])->value = std::rand() % MAX_VALUE;
                } else {
                    network->layers[i].emplace_back(new OutputNode(activationFunctionMap(activations[i - 1]), std::rand() % DOUBLE_MAX_BIAS - DOUBLE_MAX_BIAS * 0.5));
                    for (auto* prevNode : network->layers[i - 1]) {
                        ((OutputNode*) network->layers[i][j])->addConnection(prevNode, std::rand() % DOUBLE_MAX_WEIGHT - DOUBLE_MAX_WEIGHT * 0.5);
                    }
                }
            }
        }

        return network;
    }

    std::vector<double> calculateOutputLayer() {
        std::vector<double> ret = {};
        for (auto* node : layers[layers.size() - 1]) {
            ret.emplace_back(node->calculateOutput());
        }
        return ret;
    }

    void setInputLayer(std::vector<double> inputs) {
        for (unsigned long i = 0; i < inputs.size(); i++) {
            ((InputNode*)layers[0][i])->value = inputs[i];
        }
    }

    std::vector<Node*> operator[] (int index) {
        return layers[index];
    }
};

#endif //BACKPROP_FFNETWORK_HPP
