//
// Created by Chris Purdy on 23/10/2021.
//

#ifndef BACKPROP_NODE_HPP
#define BACKPROP_NODE_HPP

#include <utility>
#include <vector>
#include <tic.h>

using Weight = double;

class Node {
public:
    Node() = default;
    virtual double calculateOutput() {
        return 0.0;
    };
};

class OutputNode : public Node {
private:
    std::function<double(double)> activationFunction;
    double bias;

    // These are the *incoming* connections to this node
    std::vector<std::pair<Node*, Weight>> connections;

public:
    OutputNode(std::function<double(double)> activationFunction, double bias) {
        this->activationFunction = std::move(activationFunction);
        this->bias = bias;
        this->connections = {};
    }

    void addConnection(Node* n, Weight w) {
        connections.emplace_back(n, w);
    }

    double calculateOutput() override {
        //std::cout << "Calling calculateOutput on OUTPUT node" << std::endl;
        double sum = 0;
        for (auto connection : connections) {
            sum += connection.first->calculateOutput() * connection.second;
        }
        return activationFunction(sum) + bias;
    }
};

class InputNode : public Node {
public:
    double value;

    InputNode() {
        this->value = 0;
    }

    InputNode(double value) {
        this->value = value;
    }

    double calculateOutput() override {
        //std::cout << "Calling calculateOutput on INPUT node, value is: " << value << std::endl;
        return value;
    }
};


#endif //BACKPROP_NODE_HPP
