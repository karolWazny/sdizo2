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
    void displayList();
    void dijkstra();
    void bellmanFord();

    GraphPointer listGraph = GraphPointer(new ListGraph(0));
    GraphPointer matrixGraph = GraphPointer(new MatrixGraph(0));
};


#endif //SDIZO2_DIRECTEDOPERATIONS_H
