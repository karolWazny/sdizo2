#include "Main.h"

int Main::run() {
    displayGreeting();
    while(keepGoing)
    {
        displayMenu();
        std::getline(std::cin, input);
        interpretInput();
    }
    return 0;
}

void Main::displayGreeting() {
    std::wcout << "Witamy w programie." << std::endl << std::endl;
}

void Main::displayMenu() {
    String menuText = "1. Szukanie najkrotszych sciezek (grafy skierowane).\n";
    menuText += "2. Wyznaczanie MST (grafy nieskierowane).\n";
    menuText += "3. Zakoncz program.\n";
    std::cout << menuText;
}

void Main::interpretInput() {
    int option;
    try{
        option = std::stoi(input);
        switch(option){
            case 1:
                mst();
                break;
            case 2:
                shortestPaths();
                break;
            case 3:
                keepGoing = false;
                break;
            default:
                throw 4;
        }
    } catch (...) {
        std::wcout << L"Niewlasciwy symbol." << std::endl;
        return;
    }
}

void Main::mst() {

}

void Main::shortestPaths() {

}
