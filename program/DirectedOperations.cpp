#include "DirectedOperations.h"

DirectedOperations::DirectedOperations() {
    header = "GRAFY SKIEROWANE";
    firstAlgorithm = "Algorytm Dijkstry";
    secondAlgorithm = "Algorytm Belmana-Forda";
}

void DirectedOperations::run() {
    active = true;
    while(active)
    {
        menu();
        std::getline(std::cin, input);
        interpretInput();
    }
}

void DirectedOperations::menu() {
    displayMenu();
}

void DirectedOperations::interpretInput() {
    int option;
    try{
        option = std::stoi(input);
        switch(option){
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                active = false;
                break;
            default:
                throw 4;
        }
    } catch (...) {
        std::wcout << L"Niewlasciwy symbol." << std::endl;
        return;
    }
}
