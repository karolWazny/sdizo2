#ifndef SDIZO2_OPERATIONS_H
#define SDIZO2_OPERATIONS_H


#include <string>
#include "Randomizer.h"

class Operations {
public:
    void displayMenu();
    void read();
    int readInt();
    std::string readStr();
    int sizeChoiceMenu(int[], int);
    int randomInt();
    int randomInt(int);
protected:
    std::string input;
    bool active;

    std::string header;
    std::string firstAlgorithm;
    std::string secondAlgorithm;

    Randomizer randomizer = Randomizer();
};

#endif //SDIZO2_OPERATIONS_H
