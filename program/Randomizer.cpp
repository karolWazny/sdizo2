#include "Randomizer.h"

Randomizer::Randomizer() {
    generator = std::mt19937(randomDevice());
    distribution = std::uniform_int_distribution<>(1, INT_MAX);
}

int Randomizer::getInt() {
    return distribution(generator);
}

int Randomizer::getInt(int max) {
    auto distrib = std::uniform_int_distribution<>(0, max);
    return distrib(generator);
}