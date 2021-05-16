#include "TextFileReader.h"

#include <iostream>

std::shared_ptr<int32_t[]> TextFileReader::fromFile(std::string filename) {
    read(filename);
    auto output = fileContent;
    return output;
}

void TextFileReader::read(std::string filename) {
    std::ifstream stream;
    stream.open(filename);
    std::string buffer;
    int edgesAmount;
    stream >> edgesAmount;
    int dataSize = 2 + edgesAmount * 3;
    stream >> dataSize;
    auto fileContent = std::shared_ptr<int32_t[]>(new int32_t[dataSize]);
    fileContent[0] = edgesAmount;
    for(int i = 1; i < dataSize; i++)
    {
        stream >> fileContent[i];
    }
    this->fileContent = fileContent;
}
