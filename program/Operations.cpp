#include "Operations.h"
#include <iostream>

void Operations::displayMenu() {
    std::string menuText;
    menuText += header;
    menuText += "\n1. Zbuduj z pliku\n"
                "2. Wygeneruj losowo\n"
                "3. Wyswietl listowo\n"
                "4. Wyswietl macierzowo\n"
                "5. ";
    menuText += firstAlgorithm;
    menuText += "\n6. ";
    menuText += secondAlgorithm;
    menuText += "\n7. Pomiar czasu\n"
                "8. Wroc do menu glownego\n\n";
    std::cout << menuText;
}

void Operations::read() {
    std::getline(std::cin, input);
}

int Operations::readInt() {
    read();
    return std::stoi(input);
}

int Operations::sizeChoiceMenu(int *possibilities, int numberOfPossibilities) {
    std::string text;
    for(int i = 0; i < numberOfPossibilities; i++)
    {
        text += std::to_string(i + 1);
        text += ". ";
        text += std::to_string(possibilities[i]);
        text += "\n";
    }
    std::cout << text;
    int option = readInt();
    if(option > numberOfPossibilities)
        throw 4;
    return possibilities[option - 1];
}

std::string Operations::readStr() {
    read();
    return input;
}

int Operations::randomInt() {
    return randomizer.getInt();
}

int Operations::randomInt(int max) {
    return randomizer.getInt(max);
}
