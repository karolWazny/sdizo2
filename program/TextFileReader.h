#ifndef SDIZO2_TEXTFILEREADER_H
#define SDIZO2_TEXTFILEREADER_H

#include <memory>
#include <string>
#include <fstream>

class TextFileReader {
public:
    std::unique_ptr<int32_t[]> fromFile(std::string filename);

private:
    void read(std::string);

    std::unique_ptr<int32_t[]> fileContent;
};

#endif //SDIZO2_TEXTFILEREADER_H
