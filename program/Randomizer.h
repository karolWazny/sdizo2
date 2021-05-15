#ifndef SDIZO2_RANDOMIZER_H
#define SDIZO2_RANDOMIZER_H

#include <random>

class Randomizer {
public:
    Randomizer();
    int getInt();
    int getInt(int);
private:
    std::random_device randomDevice;
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};

#endif //SDIZO2_RANDOMIZER_H
