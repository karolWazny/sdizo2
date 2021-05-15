#include "TextFileReader.h"

#include <iostream>

std::unique_ptr<int32_t[]> TextFileReader::fromFile(std::string filename) {
    read(filename);
    auto output = std::move(fileContent);
    return output;
}

void TextFileReader::read(std::string filename) {
    std::ifstream stream;
    stream.open(filename);
    std::string buffer;
    int dataSize;
    stream >> dataSize;
    auto fileContent = std::make_unique<int32_t[]>(dataSize + 1);
    fileContent[0] = dataSize;
    for(int i = 1; i <= dataSize; i++)
    {
        stream >> fileContent[i];
    }
    this->fileContent = std::move(fileContent);
}
