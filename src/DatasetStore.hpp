//
// Created by Chris Purdy on 23/10/2021.
//

#ifndef BACKPROP_DATASETSTORE_HPP
#define BACKPROP_DATASETSTORE_HPP

#include <utility>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "FileLoader/FileLoader.h"

struct Digit {
    uint8_t label;
    unsigned char pixels[28 * 28];
};

class DatasetStore {
public:

    std::vector<Digit*> dataset;

    DatasetStore(std::string labelsFilePath, std::string digitsFilePath) {
        dataset = {};
        loadData(std::move(labelsFilePath), std::move(digitsFilePath));
    }

    void loadData(std::string labelsFilePath, std::string digitsFilePath) {
        // Load labels
        auto labelFL = FileLoader(std::move(labelsFilePath));
        int32_t magicNumber;
        labelFL.addVariable((unsigned char *) &magicNumber, 0, 4);
        unsigned char labels[60000];
        labelFL.addVariable(labels,8, 60008);
        labelFL.read();

        // Load digits
        auto digitFL = FileLoader(std::move(digitsFilePath));
        digitFL.addVariable((unsigned char *) &magicNumber, 0, 4);
        unsigned char* digits = (unsigned char *)calloc(60000 * 28 * 28, sizeof(unsigned char));
        digitFL.addVariable(digits, 16, 16 + (28 * 28 * 60000));
        //auto digitFunc = std::function<int32_t(unsigned long)>([](int32_t n){ return 16 + (28 * 28 * n); });
        //digitFL.addDepVariable(digits, &numberOfItems, 16, digitFunc);
        digitFL.read();

        for(int i = 0; i < 60000; i++) {
            //std::cout << (int)labels[i] << std::endl;
            //showDigit(digits + (i * 28 * 28));
            auto* d = new Digit();
            d->label = labels[i];
            memcpy(d->pixels, digits + (i * 28 * 28), sizeof(unsigned char) * 28 * 28);
            dataset.emplace_back(d);
        }

        free(digits);
    }

    static void showDigit(const double* pixels) {
        for (int i = 27; i >= 0; i--) {
            for (int j = 27; j >= 0; j--) {
                printf(((int)pixels[j + i*28]) <= 128 ? "  " : "00");
            }
            printf("\n");
        }
    }

    int getLabel(unsigned long i);

    std::vector<double> getDigit(unsigned long i);

};


#endif //BACKPROP_DATASETSTORE_HPP
