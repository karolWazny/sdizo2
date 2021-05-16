#ifndef SDIZO2_RANDOMIZER_H
#define SDIZO2_RANDOMIZER_H

#include <random>

class Randomizer {
public:
    Randomizer();
    int getInt();
    int getInt(int);
    unsigned long getULong();
    unsigned long getULong(unsigned long max);
    bool getBool(unsigned long hits, unsigned long omega);
private:
    std::random_device randomDevice;
    std::mt19937_64 generator;
    std::uniform_int_distribution<unsigned long> distribution;
};

#endif //SDIZO2_RANDOMIZER_H
