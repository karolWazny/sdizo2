#ifndef SDIZO2_UNDIRECTEDOPERATIONS_H
#define SDIZO2_UNDIRECTEDOPERATIONS_H

#include "Operations.h"
#include <iostream>

class UndirectedOperations : public Operations {
public:
    UndirectedOperations();
    void run();
private:
    void menu();
    void interpretInput();
};


#endif //SDIZO2_UNDIRECTEDOPERATIONS_H
