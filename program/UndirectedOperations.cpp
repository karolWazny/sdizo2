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
                fromFile();
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
        std::cout << "Niewlasciwy symbol." << std::endl;
        return;
    }
}

void UndirectedOperations::fromFile() {
    std::string text = "Wprowadz nazwe, sciezke wzgledem aktualnego folderu,\n"
                       "lub pelna sciezke do pliku:\n";
    std::cout << text;
    std::string filename;
    std::getline(std::cin, filename);
    try {
        TextFileReader reader;
        auto content = reader.fromFile(filename);
        auto generator = GraphGenerator();
        matrixGraph = generator.buildGraphUndirected(FactoryPointer(new MatrixGraphFactory), content);
        listGraph = generator.buildGraphUndirected(FactoryPointer(new ListGraphFactory), content);
    } catch(...) {
        std::cout << "Wystapil problem.\n"
                     "Operacje anulowano.\n";
    }
}
