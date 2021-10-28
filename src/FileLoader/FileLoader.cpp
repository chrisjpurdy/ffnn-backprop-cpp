//
// Created by Chris Purdy on 23/10/2021.
//

#include <iostream>
#include "FileLoader.h"

void FileLoader::read() {
    std::ifstream fin(filePath);
    char c;
    unsigned long i = 0;

    while (fin.get(c)) {
        if (i >= indexMap.size()) {
            break;
        }
        switch (indexMap[i]) {
            case POINTER:
                memcpy(pointerMap[i], &c, sizeof(unsigned char));
                break;
            case DEPENDENT_POINTER:
                // Call dep function here
                /*
                {
                    auto data = pointerMap[i].depPointer;
                    std::function<unsigned long(void *)> f = std::get<2>(data);
                    addVariable(std::get<0>(data), i, f(std::get<1>(data)));
                    memcpy(pointerMap[i].pointer, &c, sizeof(unsigned char));
                }
                break;
                */
            case NONE:
            default:
                break;

        }
        i++;
    }
    fin.close();
}

void FileLoader::addVariable(unsigned char *var, unsigned long startByte, unsigned long endByte) {
    auto pointer = var;

    if (endByte > pointerMap.size()) {
        pointerMap.resize(endByte);
        indexMap.resize(endByte, NONE);
    }
    for (long i = endByte - 1; i >= startByte && i != -1; i--) {
        pointerMap[i] = pointer;
        indexMap[i] = POINTER;
        pointer++;
    }
}

/*
template<typename T>
void FileLoader::addDepVariable(unsigned char *var, T *dep, unsigned long startByte, std::function<T(unsigned long)> depFunc) {
    if (startByte > pointerMap.size()) {
        pointerMap.resize(startByte);
        indexMap.resize(startByte, NONE);
    }
    pointerMap[startByte].depPointer = std::tuple(var, (void*)dep, std::function([depFunc](void* ptr){return depFunc((T*)ptr);}));
    indexMap[startByte] = DEPENDENT_POINTER;
}
*/