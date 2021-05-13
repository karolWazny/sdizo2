#ifndef SDIZO2_PATH_H
#define SDIZO2_PATH_H

#include <memory>
#include "../structure_templates_lib/structures.h"

class Path;

using PathPointer = std::shared_ptr<Path>;

class Path {
public:
    LinkedList<unsigned> vertices;
    long long totalWeight{0};
};

#endif //SDIZO2_PATH_H
