//
// Created by Chris Purdy on 23/10/2021.
//

#include "DatasetStore.hpp"

std::vector<double> DatasetStore::getDigit(unsigned long i) {
    std::vector<double> ret = {};
    ret.reserve(28 * 28);
    for (int j = 0; j < 28 * 28; j++) {
        ret.emplace_back((int)dataset[i]->pixels[j] * 1.0);
    }
    return ret;
}

int DatasetStore::getLabel(unsigned long i) {
    return dataset[i]->label;
}
