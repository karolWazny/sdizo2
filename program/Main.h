#ifndef SDIZO2_MAIN_H
#define SDIZO2_MAIN_H

#include <string>
#include <iostream>

#include "DirectedOperations.h"
#include "UndirectedOperations.h"
#include "TimeMeasurer.h"

using String = std::string;

class Main
{
public:
    int run();
private:
    static void displayGreeting();
    static void displayMenu();
    void interpretInput();
    void mst();
    void shortestPaths();
    void measurements();
    bool keepGoing = true;
    String input;

    DirectedOperations directed;
    UndirectedOperations undirected;
    TimeMeasurer timeMeasurer;
};


#endif //SDIZO2_MAIN_H
