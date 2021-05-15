#ifndef SDIZO2_DIRECTEDOPERATIONS_H
#define SDIZO2_DIRECTEDOPERATIONS_H

#include <iostream>
#include "Operations.h"

class DirectedOperations : public Operations {
public:
    DirectedOperations();
    void run();
private:
    void menu();
    void interpretInput();
};


#endif //SDIZO2_DIRECTEDOPERATIONS_H
