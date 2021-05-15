#ifndef SDIZO2_MAIN_H
#define SDIZO2_MAIN_H

#include <string>
#include <iostream>

using String = std::string;

class Main
{
public:
    int run();
    static void displayGreeting();
    static void displayMenu();
    void interpretInput();
    void mst();
    void shortestPaths();
private:
    bool keepGoing = true;
    String input;
};


#endif //SDIZO2_MAIN_H
