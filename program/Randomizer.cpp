#include "Randomizer.h"

Randomizer::Randomizer() {
    generator = std::mt19937_64(randomDevice());
    distribution = std::uniform_int_distribution<unsigned long>();
}

int Randomizer::getInt() {
    return getInt(INT32_MAX);
}

int Randomizer::getInt(int max) {
    auto distrib = std::uniform_int_distribution<>(0, max);
    return distrib(generator);
}

unsigned long Randomizer::getULong() {
    return distribution(generator);
}

unsigned long Randomizer::getULong(unsigned long max) {
    auto distrib = std::uniform_int_distribution<unsigned long long>(0, max);
    return distrib(generator);
}

bool Randomizer::getBool(unsigned long hits, unsigned long omega) {
    if(!hits)
        return false;
    if(hits > omega)
        throw std::exception();
    return getULong(omega - 1) < hits;
}
