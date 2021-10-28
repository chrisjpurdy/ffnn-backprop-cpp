//
// Created by Chris Purdy on 23/10/2021.
//
#include <iostream>
#include "FFNetwork.hpp"

void FFNetwork::backpropagation(std::vector<double> input, std::vector<double> expected_output) {
    if (layers[0].size() != input.size()) {
        std::cerr << "Input was not the same size as input layer! Cannot perform backpropagation" << std::endl;
        return;
    }
    if (layers[layers.size()-1].size() != expected_output.size()) {
        std::cerr << "Output was not the same size as output layer! Cannot perform backpropagation" << std::endl;
        return;
    }

    // Fill this in!


}