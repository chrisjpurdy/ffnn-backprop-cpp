//
// Created by Chris Purdy on 23/10/2021.
//

#ifndef BACKPROP_FILELOADER_H
#define BACKPROP_FILELOADER_H

#include <string>
#include <utility>
#include <vector>
#include <fstream>

enum IndexType {
    NONE,
    POINTER,
    DEPENDENT_POINTER
};

/*
union PointerType {
    unsigned char* pointer;
    std::tuple<unsigned char*, void*, std::function<unsigned long(void*)>> depPointer;

    PointerType() {
        pointer = nullptr;
    }

    PointerType(PointerType const &p) {
        this->pointer = p.pointer;
        this->depPointer = std::tuple<unsigned char*, void*, std::function<unsigned long(void*)>>(p.depPointer);
    }

    PointerType& operator=(PointerType p) {
        this->pointer = p.pointer;
        this->depPointer = std::tuple<unsigned char*, void*, std::function<unsigned long(void*)>>(p.depPointer);
        return *this;
    }

    ~PointerType() {
        delete pointer;
    }
};
*/

class FileLoader {
private:
    // Maps from a byte index to a pointer to the variable that should contain the value
    std::vector<unsigned char*> pointerMap;
    std::vector<IndexType> indexMap;

    std::string filePath;

public:

    FileLoader(std::string filePath) {
        this->filePath = std::move(filePath);
        pointerMap = {};
        indexMap = {};
    }

    FileLoader(char filePath[]) {
        FileLoader(std::basic_string(filePath));
    }

    // The variable pointed to by var must have at least (endByte - startByte) bytes of memory given to it
    void addVariable(unsigned char *var, unsigned long startByte, unsigned long endByte);

    template<typename T>
    void addDepVariable(unsigned char *var, T *dep, unsigned long startByte, std::function<T(unsigned long)> depFunc);

    void read();
};


#endif //BACKPROP_FILELOADER_H
