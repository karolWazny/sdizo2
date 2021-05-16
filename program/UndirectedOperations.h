#ifndef SDIZO2_UNDIRECTEDOPERATIONS_H
#define SDIZO2_UNDIRECTEDOPERATIONS_H

#include "Operations.h"
#include <iostream>
#include "../graphs/GraphGenerator.h"
#include "../graphs/MatrixGraphFactory.h"
#include "../graphs/ListGraphFactory.h"

class UndirectedOperations : public Operations {
public:
    UndirectedOperations();
    void run();
private:
    void menu();
    void interpretInput();
    void fromFile();

    GraphPointer listGraph;
    GraphPointer matrixGraph;
};


#endif //SDIZO2_UNDIRECTEDOPERATIONS_H
