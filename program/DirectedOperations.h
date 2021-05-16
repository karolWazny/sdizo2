#ifndef SDIZO2_DIRECTEDOPERATIONS_H
#define SDIZO2_DIRECTEDOPERATIONS_H

#include <iostream>
#include "Operations.h"
#include "../graphs/GraphGenerator.h"
#include "../graphs/MatrixGraphFactory.h"
#include "../graphs/ListGraphFactory.h"

class DirectedOperations : public Operations {
public:
    DirectedOperations();
    void run();
private:
    void menu();
    void interpretInput();
    void fromFile();

    GraphPointer listGraph;
    GraphPointer matrixGraph;
};


#endif //SDIZO2_DIRECTEDOPERATIONS_H
