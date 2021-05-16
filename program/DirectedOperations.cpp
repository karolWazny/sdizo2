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
                fromFile();
                break;
            case 2:
                break;
            case 3:
                displayList();
                break;
            case 4:
                break;
            case 5:
                dijkstra();
                break;
            case 6:
                bellmanFord();
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

void DirectedOperations::fromFile() {
    std::string text = "Wprowadz nazwe, sciezke wzgledem aktualnego folderu,\n"
                       "lub pelna sciezke do pliku:\n";
    std::cout << text;
    std::string filename;
    std::getline(std::cin, filename);
    try {
        TextFileReader reader;
        auto content = reader.fromFile(filename);
        auto generator = GraphGenerator();
        matrixGraph = generator.buildGraphDirected(FactoryPointer(new MatrixGraphFactory), content);
        listGraph = generator.buildGraphDirected(FactoryPointer(new ListGraphFactory), content);
    } catch(...) {
        std::cout << "Wystapil problem.\n"
                     "Operacje anulowano.\n";
    }
}

void DirectedOperations::displayList() {
    std::cout << listGraph->getRepresentation() << std::endl;
}

void DirectedOperations::dijkstra() {
    std::cout << "Podaj poczatkowy wierzcholek:\n";
    int initial = readInt();
    std::cout << "Podaj koncowy wierzcholek:\n";
    int final = readInt();
    std::cout << "Jaka reprezentacje chcesz testowac?\n"
                 "1. Listowa.\n"
                 "2. Macierzowa.\n";
    int option = readInt();
    PathPointer path;
    switch(option) {
        case 1:
            path = listGraph->shortestPathDijkstra(initial, final);
            break;
        case 2:
            path = matrixGraph->shortestPathDijkstra(initial, final);
            break;
        default:
            throw 4;
    }
    if(path->totalWeight != INT64_MAX) {
        std::cout << "Wierzcholki na sciezce:\n";
        std::cout << path->vertices.toString() << std::endl;
        std::cout << "Calkowity koszt sciezki: " << std::to_string(path->totalWeight);
        std::cout << std::endl;
        return;
    } else {
        std::cout << "Nie ma sciezki z podanego wierzcholka\n"
                     "poczatkowego do koncowego.\n";
    }
}

void DirectedOperations::bellmanFord() {
    std::cout << "Podaj poczatkowy wierzcholek:\n";
    int initial = readInt();
    std::cout << "Podaj koncowy wierzcholek:\n";
    int final = readInt();
    std::cout << "Jaka reprezentacje chcesz testowac?\n"
                 "1. Listowa.\n"
                 "2. Macierzowa.\n";
    int option = readInt();
    PathPointer path;
    switch(option) {
        case 1:
            path = listGraph->shortestPathBF(initial, final);
            break;
        case 2:
            path = matrixGraph->shortestPathBF(initial, final);
            break;
        default:
            throw 4;
    }
    if(path->totalWeight != INT64_MAX) {
        std::cout << "Wierzcholki na sciezce:\n";
        std::cout << path->vertices.toString() << std::endl;
        std::cout << "Calkowity koszt sciezki: " << std::to_string(path->totalWeight);
        std::cout << std::endl;
        return;
    } else {
        std::cout << "Nie ma sciezki z podanego wierzcholka\n"
                     "poczatkowego do koncowego.\n";
    }
}
