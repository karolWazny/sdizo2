#include "UndirectedOperations.h"

UndirectedOperations::UndirectedOperations() {
    header = "GRAFY NIESKIEROWANE";
    firstAlgorithm = "Algorytm Prima";
    secondAlgorithm = "Algorytm Kruskala";
}

void UndirectedOperations::run() {
    active = true;
    while(active)
    {
        menu();
        std::getline(std::cin, input);
        interpretInput();
    }
}

void UndirectedOperations::menu() {
    displayMenu();
}

void UndirectedOperations::interpretInput() {
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